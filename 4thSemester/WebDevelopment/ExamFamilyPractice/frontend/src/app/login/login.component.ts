import { Component } from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  family = {
    user: '',
    mother: '',
    father: ''
  }

  constructor(private service: ServiceComponent, private router: Router) {}
  login(){
    this.service.login(this.family.user, this.family.mother, this.family.father).subscribe((response: any) => {
      localStorage.setItem('userId', response);
      localStorage.setItem('user', this.family.user);
      this.router.navigateByUrl("/browse");
    }, (error: any) => {
      alert(error.error);
    });
  }

}
