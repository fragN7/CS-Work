import {Component, OnInit} from '@angular/core';
import {Rule, ServiceComponent, Workflow} from '../../../service/service.component';
import {AuthService} from '../../../service/authentication/authentication.service';
import {Router} from '@angular/router';

export interface RuleUI extends Rule {
  selected?: boolean;
}

@Component({
  selector: 'app-rule',
  standalone: false,
  templateUrl: './rule.component.html',
  styleUrl: './rule.component.css'
})
export class RuleComponent implements OnInit{
  rules: RuleUI[] = [];
  username?: string = '';
  // Filter fields
senderFilter: string = '';
objectTypeFilter: string = '';
receiverFilter: string = '';
workflowFilter: string = '';

// Computed filtered list
get filteredRules() {
  return this.rules.filter(rule =>
    (!this.senderFilter || rule.sender?.toLowerCase().includes(this.senderFilter.toLowerCase())) &&
    (!this.objectTypeFilter || rule.objectType?.toLowerCase().includes(this.objectTypeFilter.toLowerCase())) &&
    (!this.receiverFilter || rule.receiver?.toLowerCase().includes(this.receiverFilter.toLowerCase())) &&
    (!this.workflowFilter || rule.workflow?.name?.toLowerCase().includes(this.workflowFilter.toLowerCase()))
  );
}

  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router) { }

  ngOnInit() {
    this.getRules();
    this.username = localStorage.getItem('user')?.toString();
  }

  userLogout(){
    this.userService.logout();
  }

  getRules(){
    this.service.getRules().subscribe(
      (response: RuleUI[]) => {
        this.rules = response.map(rl => ({ ...rl, selected: false }));
      },
      (error: any) => {
        console.error('Error fetching rules: ', error);
      }
    )
  }

  getSelectedRules(): Rule[] {
    return this.rules.filter(rl => rl.selected);
  }

  toggleSelect(rule: RuleUI): void {
    rule.selected = !rule.selected;
  }

  canEdit(): boolean {
    return this.getSelectedRules().length === 1;
  }

  canCopy(): boolean {
    return this.getSelectedRules().length === 1;
  }

  canDelete(): boolean {
    return this.getSelectedRules().length > 0;
  }

  createRule(): void {
    this.router.navigateByUrl(`rule/create`);
  }

  editRule(): void {
    const selected = this.getSelectedRules();
    if (selected.length === 1) {
      this.router.navigateByUrl(`rule/configure/${selected[0].id}`);
      localStorage.setItem('ruleId', selected[0].id.toString());
      localStorage.setItem('saveType', 'edit');
    }
  }

  copyRule(): void {
    const selected = this.getSelectedRules();
    if (selected.length === 1) {
      this.router.navigateByUrl(`rule/create`);
      localStorage.setItem('ruleId', selected[0].id.toString());
      localStorage.setItem('saveType', 'copy');
    }
  }

  deleteRule(): void {
    const selected = this.getSelectedRules();
    if (selected.length === 0) return;

    const confirmMsg =
      selected.length === 1
        ? `Are you sure you want to delete this rule?`
        : `Are you sure you want to delete ${selected.length} workflows?`;

    if (window.confirm(confirmMsg)) {
      selected.forEach(rule => {
        this.service.deleteRule(rule.id).subscribe({
          next: () => {
            this.rules = this.rules.filter(rl => rl.id !== rule.id);
          },
          error: (err) => {
            console.error(`Failed to delete rule ${rule.id}`, err);
            alert('Rule in use, can not be deleted');
          }
        });
      });
    }
  }
}
