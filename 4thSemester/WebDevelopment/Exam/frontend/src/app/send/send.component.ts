import {Component, OnInit} from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-send',
  templateUrl: './send.component.html',
  styleUrls: ['./send.component.css']
})
export class SendComponent implements OnInit{

  form = {
    username: '',
    message: '',
    receivers: ''
  }
  ngOnInit() {
    this.form.username = localStorage.getItem('user')!;
    this.service.deleteMessage(this.form.username).subscribe(
      (response: any) => {},
      (error: any) => {}
    );
  }

  constructor(private service: ServiceComponent, private router: Router) {}

  sendMessage(){
    this.service.sendMessage(this.form.username, this.form.message, this.form.receivers).subscribe(
      (response: any) => {
        alert('Message sent');
        this.router.navigateByUrl("browse");
      },
      (error: any) => {
        alert(error.error);
      }
    );
  }
}
