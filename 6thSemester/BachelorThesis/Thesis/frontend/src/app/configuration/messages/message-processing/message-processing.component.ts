import {Component, OnDestroy, OnInit} from '@angular/core';
import {Message, MessageStep, Partner, Rule, ServiceComponent} from '../../../service/service.component';
import {AuthService} from '../../../service/authentication/authentication.service';
import {Router} from '@angular/router';

@Component({
  selector: 'app-message-processing',
  standalone: false,
  templateUrl: './message-processing.component.html',
  styleUrl: './message-processing.component.css'
})
export class MessageProcessingComponent implements OnInit, OnDestroy{
  stepNameFilter: string = '';
resultFilter: string = '';

  message: Message = null!;
  selectedStepId: string | null = null;
  username?: string = '';

  openTabs: any[] = [];
  selectedTabIndex = 0;
  overlayHeight = 300;
  overlayVisible = false;
  isResizing = false;
  lastY = 0;


  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router) { }

  ngOnInit() {
    const messageId = localStorage.getItem('messageId')?.toString();
    if(messageId != null){
      this.getMessageById(messageId);
    }
    this.username = localStorage.getItem('user')?.toString();
    window.addEventListener('mousemove', this.onMouseMove.bind(this));
    window.addEventListener('mouseup', this.stopResize.bind(this));
  }

  ngOnDestroy() {
    localStorage.removeItem('messageId');
    window.removeEventListener('mousemove', this.onMouseMove.bind(this));
    window.removeEventListener('mouseup', this.stopResize.bind(this));
  }

  userLogout(){
    this.userService.logout();
  }

  get filteredSteps() {
  return this.message?.messageSteps?.filter(step =>
    (!this.stepNameFilter || step.stepName?.toLowerCase().includes(this.stepNameFilter.toLowerCase())) &&
    (!this.resultFilter || step.result?.toLowerCase().includes(this.resultFilter.toLowerCase()))
  ) ?? [];
}


  getMessageById(messageId: string){
    this.service.getMessageById(messageId).subscribe(
      (response: Message) => {
        this.message = response;
        this.message.messageSteps = this.message.messageSteps.sort((a, b) => {
          const timeA = new Date(a.startedTime).getTime();
          const timeB = new Date(b.startedTime).getTime();
          return timeA - timeB; // ascending order
        });
        console.log(this.message.messageSteps);
      },
      (error: any) => {
        console.error('Error fetching partner: ', error);
      }
    )
  }

  toggleSelection(step: MessageStep) {
    if (this.selectedStepId === step.id) {
      this.selectedStepId = null; // Deselect if already selected
    } else {
      this.selectedStepId = step.id;
    }
  }

  isSelected(step: MessageStep): boolean {
    return this.selectedStepId === step.id;
  }

  allStepsReady(): boolean {
    return this.message.messageSteps.every(step => step.result === 'READY');
  }

  processStep(step: MessageStep): void {
    if (!this.message?.id || !step?.id) return;

    console.log(step);

    const confirmMsg = `Are you sure you want to process message with id"${step.id}"?`;

    if (window.confirm(confirmMsg)) {

      const now = new Date();
      const pad = (n: number): string => n.toString().padStart(2, '0');
      const formatted =
        now.getFullYear().toString() +
        pad(now.getMonth() + 1) +
        pad(now.getDate()) +
        pad(now.getHours()) +
        pad(now.getMinutes()) +
        pad(now.getSeconds());

      const fileName =
        this.message.rule.sender + "_" +
        this.message.rule.objectType + "_" +
        this.message.rule.receiver + "." +
        ((step.stepName === "CONVERT" || step.stepName === "SHELL") ? "TF" : "") +
        formatted + "_" + this.message.id;

      let cleanedPath = step.filePath.toString().replace(/^archive\\temp\\/, '');
      if (!cleanedPath){
        cleanedPath = "remove";
      }

      const sanitizedFileName = fileName.replace(/\s+/g, '');
      this.service.processMessage(cleanedPath, sanitizedFileName, step.id, step.stepName);
    }
  }

  selectStep(step: any) {
    const existingIndex = this.openTabs.findIndex(t => t.stepName === step.stepName);
    if (existingIndex === -1) {
      this.openTabs.push(step);
      this.selectedTabIndex = this.openTabs.length - 1;
    } else {
      this.selectedTabIndex = existingIndex;
    }
    this.overlayVisible = true;
  }

  selectTab(idx: number) {
    this.selectedTabIndex = idx;
    const selectedTab = this.openTabs[idx];
    if (!selectedTab.content) {
      this.loadFileContent(selectedTab, idx);
    }
  }

  loadFileContent(step: any, tabIndex: number) {
    this.service.getFileContentFromPath(step.filePath).subscribe(content => {
      this.openTabs[tabIndex].content = content;
    });
  }

  closeTab(index: number) {
    this.openTabs.splice(index, 1);
    if (this.selectedTabIndex >= this.openTabs.length) {
      this.selectedTabIndex = this.openTabs.length - 1;
    }
    if (this.openTabs.length === 0) {
      this.overlayVisible = false;
    }
  }

  startResize(event: MouseEvent) {
    this.isResizing = true;
    this.lastY = event.clientY;
    event.preventDefault();
  }

  onMouseMove(event: MouseEvent) {
    if (!this.isResizing) return;
    const dy = this.lastY - event.clientY; // because resizing upwards from top
    this.overlayHeight = Math.min(Math.max(this.overlayHeight + dy, 100), window.innerHeight * 0.9);
    this.lastY = event.clientY;
  }

  stopResize() {
    this.isResizing = false;
  }
}
