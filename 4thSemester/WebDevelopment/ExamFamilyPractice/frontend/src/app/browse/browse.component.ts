import {Component, OnInit} from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-browse',
  templateUrl: './browse.component.html',
  styleUrls: ['./browse.component.css']
})
export class BrowseComponent implements OnInit{

  siblings: any[] = [];
  mothers: any[] = [];
  fathers: any[] = [];

  constructor(private service: ServiceComponent, private route: Router) {}

  ngOnInit() {
    this.getSiblings();
    this.getMothers();
    this.getFathers();
  }

  getSiblings(){
    this.service.getSiblings().subscribe(
      (response: any) => {
        this.siblings = response;
      }, (error: any) => {
        alert(error.error);
      }
    );
  }

  getMothers(){
    this.service.getFathers().subscribe(
      (response: any) => {
        this.fathers = response;
      }, (error: any) => {
        alert(error.error);
      }
    );
  }

  getFathers(){
    this.service.getMothers().subscribe(
      (response: any) => {
        this.mothers = response;
      }, (error: any) => {
        alert(error.error);
      }
    );
  }

  goBack(){
    localStorage.removeItem('userId');
    localStorage.removeItem('user');
    this.route.navigateByUrl("/");
  }

  addRedirect(){
    this.route.navigateByUrl("add")
  }
}
