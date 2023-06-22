import { Component } from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  form = {
    username: '',
    password: ''
  }
  constructor(private service: ServiceComponent, private router: Router) {}
  login(){
    this.service.login(this.form.username, this.form.password).subscribe((response: any) => {
      localStorage.setItem('userId', response);
      localStorage.setItem('user', this.form.username);
      this.router.navigateByUrl("/browse");
    }, (error: any) => {
      alert(error.error);
    });
  }
}
