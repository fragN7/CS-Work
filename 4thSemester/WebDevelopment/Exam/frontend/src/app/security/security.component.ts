import {Component, OnInit} from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-security',
  templateUrl: './security.component.html',
  styleUrls: ['./security.component.css']
})
export class SecurityComponent implements OnInit{
  question: string = '';
  answer: string = '';
  constructor(private service: ServiceComponent, private router: Router) {}

  ngOnInit() {
    this.question = localStorage.getItem('question')!;
  }

  login(){
    const username = localStorage.getItem('user')!;
    this.service.loginSecurity(username, this.answer).subscribe((response: any) => {
      this.router.navigateByUrl("/browse");
    }, (error: any) => {
      alert(error.error);
    });
  }
}
