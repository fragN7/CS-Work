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
  actualLinks: any[] = [];

  constructor(private service: ServiceComponent, private router: Router) {}
  ngOnInit() {
    const city = localStorage.getItem('firstRoute')!;
    this.getLinks(city);

    for (const link of this.links) {
      const linkCity = this.getCity(link.firstCityId);

      const linkItem = {
        country: linkCity.name,
        myLink: link
      }

      console.log(linkItem.country);

      this.actualLinks.push(linkItem);
    }
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

  getCity(cityId: number) : any{
    this.service.getCity(cityId).subscribe(
      (response: any) => {
        return response;
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
