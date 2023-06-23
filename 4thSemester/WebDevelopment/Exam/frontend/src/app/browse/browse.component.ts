import {Component, OnInit} from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-browse',
  templateUrl: './browse.component.html',
  styleUrls: ['./browse.component.css']
})
export class BrowseComponent implements OnInit{

  messages: any[] = [];
  username: string = '';
  constructor(private service: ServiceComponent, private route: Router) {}
  ngOnInit() {
    this.username = localStorage.getItem('user')!;
    this.getMessages();
    this.service.deleteMessage(this.username).subscribe(
      (response: any) => {},
      (error: any) => {}
    );
  }

  getMessages(){
    this.service.getMessages(this.username).subscribe(
      (response: any) => {
        this.messages = response;
      }, (error: any) => {
        alert(error.error);
      });
  }

  send(){
    this.route.navigateByUrl("send");
  }

}
