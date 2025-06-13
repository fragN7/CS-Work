import {Component, OnDestroy, OnInit} from '@angular/core';
import {ServiceComponent, Workflow, WorkflowStep} from '../../../service/service.component';
import {AuthService} from '../../../service/authentication/authentication.service';
import {Router} from '@angular/router';
import {CdkDragDrop, DragDropModule, moveItemInArray, transferArrayItem} from '@angular/cdk/drag-drop';


@Component({
  selector: 'app-workflow-declaration',
  standalone: false,
  templateUrl: './workflow-declaration.component.html',
  styleUrl: './workflow-declaration.component.css'
})
export class WorkflowDeclarationComponent implements OnInit, OnDestroy{
  workflow: Workflow = { id: '', name: '', workflowSteps: [] };
  username?: string = '';
  availableSteps: string[] = ['COPY', 'SHELL', 'SEND', 'REMOVE'];
  saveType: string = '';

  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router) { }

  ngOnInit() {
    const workflowId = localStorage.getItem('workflowId')?.toString();
    if(workflowId != null){
      this.getWorkflowById(workflowId);
    }
    this.saveType = localStorage.getItem('saveType')!;
    this.username = localStorage.getItem('user')?.toString();
  }

  ngOnDestroy() {
    localStorage.removeItem('workflowId');
    localStorage.removeItem('saveType');
  }

  getWorkflowById(workflowId: string){
    this.service.getWorkflowById(workflowId).subscribe(
      (response: Workflow) => {
        this.workflow = response;
      },
      (error: any) => {
        console.error('Error fetching workflow: ', error);
      }
    )
  }

  userLogout(){
    this.userService.logout();
  }

  removeStep(index: number) {
    this.workflow.workflowSteps.splice(index, 1);
  }

  saveWorkflow() {

    const type = localStorage.getItem('saveType');
    const invalidShellStep = this.workflow.workflowSteps.find(step =>
      step.name === 'SHELL' && (!step.filePath || step.filePath.trim() === '')
    );

    if (invalidShellStep) {
      alert('Please select a folder for all Shell steps.');
      return;
    }

    if(type == 'edit'){
      this.service.editWorkflow(localStorage.getItem('workflowId')!, this.workflow.name);
    } else {
      this.service.addWorkflow(this.workflow.name, this.workflow.workflowSteps);
    }
  }
  onAvailableStepsDropped(event: CdkDragDrop<string[]>) {
    if (event.previousContainer !== event.container) {
      return;
    }
  }

  onYourStepsDropped(event: CdkDragDrop<WorkflowStep[]>) {
    if (event.previousContainer === event.container) {
      // Reorder inside Your Steps
      moveItemInArray(this.workflow.workflowSteps, event.previousIndex, event.currentIndex);
    } else {
      // Drag from availableSteps -> yourSteps: clone and insert
      const stepName = event.previousContainer.data[event.previousIndex].toString();
      const newStep: WorkflowStep = {
        id: crypto.randomUUID(),
        name: stepName,
        filePath: '',
        command: '',
        file: undefined as any,
      };
      this.workflow.workflowSteps.splice(event.currentIndex, 0, newStep);
    }
  }

  onFileSelected(event: Event, step: WorkflowStep) {
    const input = event.target as HTMLInputElement;
    if (input.files && input.files.length > 0) {
      const file = input.files![0];
      step.file = file;
      step.filePath = file.name;
    }
  }

}
