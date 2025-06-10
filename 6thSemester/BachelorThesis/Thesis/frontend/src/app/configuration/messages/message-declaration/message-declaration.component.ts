import {Component, OnInit} from '@angular/core';
import {Rule, ServiceComponent} from '../../../service/service.component';
import {AuthService} from '../../../service/authentication/authentication.service';
import {Router} from '@angular/router';
import {RuleUI} from '../../rules/rule/rule.component';

@Component({
  selector: 'app-message-declaration',
  standalone: false,
  templateUrl: './message-declaration.component.html',
  styleUrl: './message-declaration.component.css'
})
export class MessageDeclarationComponent implements OnInit{
  rules: Rule[] = [];
  filteredRules: Rule[] = [];
  selectedRule: Rule | null = null;
  selectedFile: File | null = null;
  showRules = false;

  filter = {
    sender: '',
    objectType: '',
    receiver: ''
  };

  username?: string = '';
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
      (response: Rule[]) => {
        this.rules = response;
      },
      (error: any) => {
        console.error('Error fetching rules: ', error);
      }
    )
  }

  toggleRulesDropdown() {
    this.showRules = !this.showRules;
    this.filterRules(); // Refresh filtering
  }

  filterRules() {
    this.filteredRules = this.rules.filter(rule =>
      rule.sender.toLowerCase().includes(this.filter.sender.toLowerCase()) &&
      rule.objectType.toLowerCase().includes(this.filter.objectType.toLowerCase()) &&
      rule.receiver.toLowerCase().includes(this.filter.receiver.toLowerCase())
    );
  }

  selectRule(rule: Rule) {
    this.selectedRule = rule;
    this.showRules = false;
  }

  formatRule(rule: Rule): string {
    return `${rule.sender} → ${rule.objectType} → ${rule.receiver}`;
  }

  onFileSelected(event: any) {
    const file: File = event.target.files[0];
    if (file) {
      this.selectedFile = file;
    }
  }

  sendMessage() {
    if (!this.selectedRule || !this.selectedFile) {
      alert('Please select a rule and a file first.');
      return;
    }

    this.service.addMessage(this.selectedRule, this.selectedFile);
  }

}
