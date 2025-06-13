import {Component, OnDestroy, OnInit} from '@angular/core';
import {Rule, ServiceComponent, User} from '../../../service/service.component';
import {AuthService} from '../../../service/authentication/authentication.service';
import {Router} from '@angular/router';
import {RuleUI} from '../../rules/rule/rule.component';


export interface UserUI extends User {
  selected?: boolean;
}

@Component({
  selector: 'app-user',
  standalone: false,
  templateUrl: './user.component.html',
  styleUrl: './user.component.css'
})

export class UserComponent implements OnInit{
  users: UserUI[] = [];
  username?: string = '';
  userFilter: string = '';

get filteredUsers() {
  return this.users.filter(user =>
    !this.userFilter || user.userName?.toLowerCase().includes(this.userFilter.toLowerCase())
  );
}

  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router) { }

  ngOnInit() {
    this.getUsers();
    this.username = localStorage.getItem('user')?.toString();
  }

  userLogout(){
    this.userService.logout();
  }

  getUsers(){
    this.service.getUsers().subscribe(
      (response: UserUI[]) => {
        this.users = response.map(rl => ({ ...rl, selected: false }));
      },
      (error: any) => {
        console.error('Error fetching users: ', error);
      }
    )
  }

  createUser(): void {
    localStorage.setItem('saveType', 'create');
    this.router.navigateByUrl(`user/register`);
  }

  deleteUser(): void {
    const selected = this.getSelectedUsers();
    if (selected.length === 0) return;

    const confirmMsg =
      selected.length === 1
        ? `Are you sure you want to delete "${selected[0].userName}"?`
        : `Are you sure you want to delete ${selected.length} users?`;

    if (window.confirm(confirmMsg)) {
      selected.forEach(user => {
        this.service.deleteUser(user.id).subscribe({
          next: () => {
            this.users = this.users.filter(wf => wf.id !== user.id);
          },
          error: (err) => {
            console.error(`Failed to delete User ${user.id}`, err);
            if(user.userName == "actis"){
              alert('User actis cannot be deleted');
            } else {
              alert('User in use, cannot be deleted');
            }
          }
        });
      });
    }
  }

  toggleSelect(user: UserUI): void {
    user.selected = !user.selected;
  }

  getSelectedUsers(): User[] {
    return this.users.filter(u => u.selected);
  }
  canDelete(): boolean {
    return this.getSelectedUsers().length > 0;
  }


}
