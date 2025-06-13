import {Component, OnInit} from '@angular/core';
import {Message, ServiceComponent, Workflow} from '../../../service/service.component';
import {AuthService} from '../../../service/authentication/authentication.service';
import {Router} from '@angular/router';

interface WorkflowUI extends Workflow {
  selected?: boolean;
}

@Component({
  selector:  'app-workflow',
  templateUrl: './workflow.component.html',
  standalone: false,
  styleUrl: './workflow.component.css'
})
export class WorkflowComponent implements OnInit {
  workflows: WorkflowUI[] = [];
  username?: string = '';
  nameFilter: string = '';
get filteredWorkflows() {
  return this.workflows.filter(w =>
    !this.nameFilter || w.name?.toLowerCase().includes(this.nameFilter.toLowerCase())
  );
}

  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router) { }
  
  ngOnInit() {
    this.getWorkflows();
    this.username = localStorage.getItem('user')?.toString();
  }

  userLogout(){
    this.userService.logout();
  }

  getWorkflows(){
    this.service.getWorkflows().subscribe(
      (response: WorkflowUI[]) => {
        this.workflows = response.map(wf => ({ ...wf, selected: false }));
      },
      (error: any) => {
        console.error('Error fetching workflows: ', error);
      }
    )
  }


  toggleSelect(workflow: WorkflowUI): void {
    workflow.selected = !workflow.selected;
  }

  toggleSelectAll(event: Event): void {
    const target = event.target as HTMLInputElement;
    const selected = target.checked;
    this.workflows.forEach(wf => wf.selected = selected);
  }


  isAllSelected(): boolean {
    return this.workflows.length > 0 && this.workflows.every(wf => wf.selected);
  }

  getSelectedWorkflows(): Workflow[] {
    return this.workflows.filter(wf => wf.selected);
  }

  canEdit(): boolean {
    return this.getSelectedWorkflows().length === 1;
  }

  canCopy(): boolean {
    return this.getSelectedWorkflows().length === 1;
  }

  canDelete(): boolean {
    return this.getSelectedWorkflows().length > 0;
  }

  createWorkflow(): void {
    localStorage.setItem('saveType', 'create');
    this.router.navigateByUrl(`workflow/create`);
  }

  editWorkflow(): void {
    const selected = this.getSelectedWorkflows();
    if (selected.length === 1) {
      this.router.navigateByUrl(`workflow/configure/${selected[0].id}`);
      localStorage.setItem('workflowId', selected[0].id.toString());
      localStorage.setItem('saveType', 'edit');
    }
  }

  copyWorkflow(): void {
    const selected = this.getSelectedWorkflows();
    if (selected.length === 1) {
      this.router.navigateByUrl(`workflow/create`);
      localStorage.setItem('workflowId', selected[0].id.toString());
      localStorage.setItem('saveType', 'copy');
    }
  }

  deleteWorkflow(): void {
    const selected = this.getSelectedWorkflows();
    if (selected.length === 0) return;

    const confirmMsg =
      selected.length === 1
        ? `Are you sure you want to delete "${selected[0].name}"?`
        : `Are you sure you want to delete ${selected.length} workflows?`;

    if (window.confirm(confirmMsg)) {
      selected.forEach(workflow => {
        this.service.deleteWorkflow(workflow.id).subscribe({
          next: () => {
            this.workflows = this.workflows.filter(wf => wf.id !== workflow.id);
          },
          error: (err) => {
            console.error(`Failed to delete workflow ${workflow.id}`, err);
            alert('Workflow in use, can not be deleted');
          }
        });
      });
    }
  }

}
