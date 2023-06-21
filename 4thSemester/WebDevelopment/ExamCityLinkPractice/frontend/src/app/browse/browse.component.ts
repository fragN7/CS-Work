import {Component, OnInit} from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-browse',
  templateUrl: './browse.component.html',
  styleUrls: ['./browse.component.css']
})
export class BrowseComponent implements OnInit {

  cities: any[] = [];

  constructor(private service: ServiceComponent, private route: Router) {}
  ngOnInit(){
    this.getCities();
  }

  getCities(){
    this.service.getCities().subscribe(
      (response: any) => {
        this.cities = response;
      }, (error: any) => {
        alert(error.error);
      }
    );
  }

  addRoute(city: string){
    alert('LOOL');
  }
}
