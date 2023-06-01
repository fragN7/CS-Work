import { Component } from '@angular/core';
import {AuthService} from "../service/auth.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {

  user = {
    username: '',
    password: ''
  }

  constructor(private service: AuthService, private router: Router) {}

  login(){
    const error = this.validateForm();
    if (error != '') {
      alert(error); // Stop execution if form validation fails
    }

    this.service.login(this.user.username, this.user.password).subscribe(data => {
      localStorage.setItem('user', data.username.toString());
      localStorage.setItem('token', data.token.toString());
      this.router.navigateByUrl("/browse");
    }, (error: any) => {
      if (error.error.includes("User doesn't exist")) {
        alert("User doesn't exist");
      } else if (error.error.includes("Password is incorrect")) {
        alert("Password is incorrect");
      }
    });
  }

  validateForm(){
    const { username, password } = this.user;
    let errors = '';

    if (!username) {
      errors += 'Username is required.';
    }

    if (!password) {
      errors += 'Password is required.';
    }

    return errors;
  }
}
