import { Component, HostListener, OnInit } from '@angular/core';
import { Message, ServiceComponent, User } from '../service/service.component';
import { Router } from '@angular/router';
import { AuthService } from '../service/authentication/authentication.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  standalone: false,
  styleUrl: './home.component.css'
})
export class HomeComponent implements OnInit {
  senderFilter: string = '';
  receiverFilter: string = '';
  objectTypeFilter: string = '';
  workflowIdFilter: string = '';
  statusFilter: string = '';
  assigneeFilter: string = '';


  messages: Message[] = [];
  username?: string = '';
  users: User[] = [];

  selectedMessages: Message[] = [];
  lastSelectedIndex: number | null = null;

  contextMenuVisible = false;
  contextMenuPosition = { x: 0, y: 0 };
  contextMenuTarget: Message | null = null;

  showAssignModal = false;
  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router) { }

  ngOnInit() {

    this.getMessages();
    this.getUsers();
    this.username = localStorage.getItem('user')?.toString();
  }

  get filteredMessages(): Message[] {
    return this.messages.filter(m =>
      (!this.workflowIdFilter || m.id?.toLowerCase().includes(this.workflowIdFilter.toLowerCase())) &&
      (!this.senderFilter || m.rule?.sender?.toLowerCase().includes(this.senderFilter.toLowerCase())) &&
      (!this.objectTypeFilter || m.rule?.objectType?.toLowerCase().includes(this.objectTypeFilter.toLowerCase())) &&
      (!this.receiverFilter || m.rule?.receiver?.toLowerCase().includes(this.receiverFilter.toLowerCase())) &&
      (!this.statusFilter || this.getMessageStep(m)?.toLowerCase().includes(this.statusFilter.toLowerCase())) &&
      (!this.assigneeFilter || m.user?.userName?.toLowerCase().includes(this.assigneeFilter.toLowerCase()))
    );
  }



getMessages() {
  this.service.getMessages().subscribe(
    (response: Message[]) => {
      console.log('Fetched messages:', response); // ✅ Add this
      this.messages = response;
    },
    (error: any) => {
      console.error('Error fetching messages: ', error);
    }
  );
}


  getUsers() {
    this.service.getUsers().subscribe(
      (response: User[]) => {
        this.users = response;
      },
      (error: any) => {
        console.error('Error fetching users: ', error);
      }
    )
  }

  getWorkflowStep(message: Message): string {

    const steps = message.messageSteps;
    if (!steps || steps.length === 0) {
      return 'N/A';
    }

    const sortedSteps = [...steps].sort((a, b) =>
      new Date(a.startedTime).getTime() - new Date(b.startedTime).getTime()
    );

    const allReady = sortedSteps.every(s => s.result === 'READY');
    const noneReady = sortedSteps.every(s => s.result !== 'READY');

    if (allReady) {
      return sortedSteps[0].stepName ?? 'N/A';
    }

    if (noneReady) {
      return sortedSteps[0].stepName ?? 'N/A';
    }

    const firstNonOK = sortedSteps.find(s => s.result !== 'OK');
    return firstNonOK?.stepName ?? 'N/A';
  }

  getMessageStep(message: Message): string {
    const steps = message.messageSteps;
    if (!steps || steps.length === 0) {
      return 'N/A';
    }

    const sortedSteps = [...steps].sort(
      (a, b) => new Date(a.startedTime).getTime() - new Date(b.startedTime).getTime()
    );

    const allReady = sortedSteps.every(s => s.result === 'READY');
    const noneReady = sortedSteps.every(s => s.result !== 'READY');

    if (allReady) {
      return sortedSteps[0].result ?? 'N/A';
    }

    if (noneReady) {
      return sortedSteps[0].result ?? 'N/A';
    }

    const firstNonOK = sortedSteps.find(s => s.result !== 'OK');
    return firstNonOK?.result ?? 'N/A';
  }



  userLogout() {
    this.userService.logout();
  }

  onRowClick(event: MouseEvent, message: Message, index: number) {
    event.preventDefault();

    if (event.ctrlKey || event.metaKey) {
      // Toggle selection
      const idx = this.selectedMessages.indexOf(message);
      if (idx > -1) {
        this.selectedMessages.splice(idx, 1);
      } else {
        this.selectedMessages.push(message);
      }
      this.lastSelectedIndex = index;
    } else if (event.shiftKey && this.lastSelectedIndex !== null) {
      const rangeStart = Math.min(this.lastSelectedIndex, index);
      const rangeEnd = Math.max(this.lastSelectedIndex, index);
      const newSelection = this.messages.slice(rangeStart, rangeEnd + 1);
      this.selectedMessages = [...new Set([...this.selectedMessages, ...newSelection])];
    } else {
      this.selectedMessages = [message];
      this.lastSelectedIndex = index;
    }

    this.contextMenuVisible = false;
  }

  isSelected(message: Message): boolean {
    return this.selectedMessages.includes(message);
  }

  onRightClick(event: MouseEvent, message: Message) {
    event.preventDefault();
    this.contextMenuVisible = true;
    this.contextMenuTarget = message;
    this.contextMenuPosition = { x: event.clientX, y: event.clientY };

    if (!this.selectedMessages.includes(message)) {
      this.selectedMessages = [message];
    }
  }

  onRowDoubleClick(message: Message): void {
    localStorage.setItem('messageId', message.id);
    this.router.navigate([`/message/${message.id}`]);
  }

  closeAssignModal() {
    this.showAssignModal = false;
  }

  assignUserToSelected(event: Event) {
    const messageIds = this.selectedMessages.map(m => m.id);
    let completed = 0;
    const selectElement = event.target as HTMLSelectElement;
    const userId = selectElement.value;

    messageIds.forEach(id => {
      this.service.assignMessageToUser(id, userId);
    });/*
    window.location.reload();*/
  }

  assignSelected() {
    this.showAssignModal = true;
  }

  resumeSelected() {
    const confirmMsg =
      this.selectedMessages.length === 1
        ? `Are you sure you want to resume message with id"${this.selectedMessages[0].id}"?`
        : `Are you sure you want to resume ${this.selectedMessages.length} messages?`;

    if (!window.confirm(confirmMsg)) return;
    this.contextMenuVisible = false;

    const now = new Date();
    const pad = (n: number): string => n.toString().padStart(2, '0');
    const formatted =
      now.getFullYear().toString() +
      pad(now.getMonth() + 1) +
      pad(now.getDate()) +
      pad(now.getHours()) +
      pad(now.getMinutes()) +
      pad(now.getSeconds());

    for (const message of this.selectedMessages) {
      if (!message.messageSteps || message.messageSteps.length === 0) continue;

      const readySteps = message.messageSteps.filter(
        (step: any) => step.result === "READY"
      );

      if (readySteps.length === 0) continue;

      const nextStep = readySteps.reduce((earliest: any, current: any) => {
        return new Date(current.startedTime) < new Date(earliest.startedTime) ? current : earliest;
      });

      const fileName =
        message.rule.sender + "_" +
        message.rule.objectType + "_" +
        message.rule.receiver + "." +
        ((nextStep.stepName === "CONVERT" || nextStep.stepName === "SHELL") ? "TF" : "") +
        formatted + "_" + message.id;

      let cleanedPath = nextStep.filePath?.toString().replace(/^archive\\temp\\/, '');
      if (!cleanedPath) {
        cleanedPath = "remove";
      }

      const sanitizedFileName = fileName.replace(/\s+/g, '');

      this.service.processMessage(
        cleanedPath,
        sanitizedFileName,
        nextStep.id,
        nextStep.stepName
      );
    }
  }


  restartSelected() {
    const confirmMsg =
      this.selectedMessages.length === 1
        ? `Are you sure you want to resume message with id"${this.selectedMessages[0].id}"?`
        : `Are you sure you want to resume ${this.selectedMessages.length} messages?`;

    if (!window.confirm(confirmMsg)) return;
    this.contextMenuVisible = false;

    for (const message of this.selectedMessages) {
      if (!message.messageSteps || message.messageSteps.length === 0) continue;

      const readySteps = message.messageSteps.filter(
        (step: any) => step.result === "READY"
      );

      this.service.restartMessage(message.rule, message.messageSteps[0].filePath.toString());
    }
  }

  deleteSelected() {
    console.log('Delete', this.selectedMessages);
    const selected = this.selectedMessages;
    if (selected.length === 0) return;

    const confirmMsg =
      selected.length === 1
        ? `Are you sure you want to delete message with id"${selected[0].id}"?`
        : `Are you sure you want to delete ${selected.length} messages?`;

    if (window.confirm(confirmMsg)) {
      const deletedIds: string[] = [];

      selected.forEach(message => {
        this.service.deleteMessage(message.id).subscribe({
          next: () => {
            console.log(`Delete successful ${message.id}`);
            deletedIds.push(message.id);

            // Remove message from messages array after last deletion
            if (deletedIds.length === selected.length) {
              this.messages = this.messages.filter(
                msg => !deletedIds.includes(msg.id)
              );
              this.selectedMessages = [];
            }
          },
          error: (err) => {
            console.error(`Failed to delete message ${message.id}`, err);
            alert('Message in use, can not be deleted');
          }
        });
      });
    }
    this.contextMenuVisible = false;
  }

  @HostListener('document:click')
  hideContextMenu() {
    this.contextMenuVisible = false;
  }

}
