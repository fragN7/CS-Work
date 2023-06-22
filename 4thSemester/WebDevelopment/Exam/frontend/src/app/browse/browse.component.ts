import {Component, OnInit} from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-browse',
  templateUrl: './browse.component.html',
  styleUrls: ['./browse.component.css']
})
export class BrowseComponent implements OnInit{

  data: any[] = [];

  constructor(private service: ServiceComponent, private route: Router) {}
  ngOnInit() {

  }

  goBack(){
    localStorage.removeItem('userId');
    localStorage.removeItem('user');
    this.route.navigateByUrl("/");
  }
}
