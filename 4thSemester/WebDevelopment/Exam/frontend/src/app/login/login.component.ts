import { Component } from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  username: string = '';
  constructor(private service: ServiceComponent, private router: Router) {}
  login(){
    this.service.login(this.username).subscribe((response: any) => {
      localStorage.setItem('user', this.username);
      localStorage.setItem('question', response.secretQuestion);
      this.router.navigateByUrl("/security");
    }, (error: any) => {
      alert(error.error);
    });
  }
}
