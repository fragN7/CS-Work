import { Component } from '@angular/core';
import {AuthService} from '../service/authentication/authentication.service';
import {Router} from '@angular/router';
import {FormsModule} from '@angular/forms';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  standalone: false,
  styleUrl: './login.component.css'
})
export class LoginComponent {

  user = {
    userName: '',
    password: '',
    hostName: '',
    port: ''
  }

  constructor(private service: AuthService, private router: Router) {}

  login(){
    const error = this.validateForm();
    if (error != '') {
      alert(error); // Stop execution if form validation fails
    }

    this.service.login(this.user.userName, this.user.password, this.user.hostName, this.user.port).subscribe(data => {
      localStorage.setItem('user', data.userName.toString());
      localStorage.setItem('token', data.token.toString());
      localStorage.setItem('userId', data.id.toString());
      localStorage.setItem('myURL', `https://${this.user.hostName}:${this.user.port}/api`);
      this.router.navigateByUrl("/");
    }, (error: any) => {
        console.log("Error object:", error);
        console.log("Error.error:", error.error);

        if (typeof error.error === 'string') {
          if (error.error.includes("User doesn't exist")) {
            alert("User doesn't exist");
          } else if (error.error.includes("Password is incorrect")) {
            alert("Password is incorrect");
          } else {
            alert(`Server https://${this.user.hostName}:${this.user.port} is offline`);
          }
        } else {
          alert(`Server https://${this.user.hostName}:${this.user.port} is offline`);
        }
      }
    );
  }

  validateForm(){
    const { userName, password } = this.user;
    let errors = '';

    if (!userName) {
      errors += 'Username is required.';
    }

    if (!password) {
      errors += 'Password is required.';
    }

    return errors;
  }
}
