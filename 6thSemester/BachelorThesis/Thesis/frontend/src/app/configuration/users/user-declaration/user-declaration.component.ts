import {Component, OnInit} from '@angular/core';
import {ServiceComponent} from '../../../service/service.component';
import {AuthService} from '../../../service/authentication/authentication.service';
import {Router} from '@angular/router';

@Component({
  selector: 'app-user-declaration',
  standalone: false,
  templateUrl: './user-declaration.component.html',
  styleUrl: './user-declaration.component.css'
})
export class UserDeclarationComponent implements OnInit{

  username?: string = '';
  user = {
    userName: '',
    password: '',
    confirmPassword: ''
  }

  showPassword = false;
  showConfirmPassword = false;

  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router) { }

  ngOnInit() {
    this.username = localStorage.getItem('user')?.toString();
  }

  userLogout(){
    this.userService.logout();
  }

  saveUser(){
    if(this.user.password !== this.user.confirmPassword){
      alert("Passwords do not match");
      return;
    }

    this.service.registerUser(this.user.userName, this.user.password).subscribe(
      response => {
        console.log("User registered successfully", response);
        this.router.navigateByUrl(`/users`);
      },
      error => {
        console.error("Error while adding user", error.error);

        let rawError = error.error;
        let message = '';

        if (typeof rawError === 'string') {
          const match = rawError.match(/System\.Exception:\s*(.*)/);
          if (match && match[1]) {
            message = match[1].split('\n')[0].trim();
          } else {
            message = rawError.split('\n')[0].trim();
          }
        } else {
          message = 'An unknown error occurred.';
        }

        alert(`Error while adding user:\n${message}`);
      }
    );
  }
}
