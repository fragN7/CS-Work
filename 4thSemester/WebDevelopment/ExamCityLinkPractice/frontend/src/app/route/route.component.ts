import {Component, OnInit} from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";
import {NgFor} from "@angular/common";

@Component({
  selector: 'app-route',
  templateUrl: './route.component.html',
  styleUrls: ['./route.component.css']
})
export class RouteComponent implements OnInit {

  links: any[] = [];

  constructor(private service: ServiceComponent, private router: Router) {}
  ngOnInit() {
    const city = localStorage.getItem('firstRoute')!;
    this.getLinks(city);

    // TODO: Associate cities to links
  }

  getLinks(city: string){
    this.service.getLinks(city).subscribe(
      (response: any) => {
        this.links = response;
      }, (error: any) => {
        alert(error.error);
      }
    );
  }

  selectRoute(link: string){
    alert('Ill cont');
  }

  endTrip(){
    this.router.navigateByUrl('');
  }
}
