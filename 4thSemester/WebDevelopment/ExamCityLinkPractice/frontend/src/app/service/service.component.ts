import { Component } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Router} from "@angular/router";

@Component({
  selector: 'app-service',
  templateUrl: './service.component.html',
  styleUrls: ['./service.component.css']
})
export class ServiceComponent {

  private URL = 'https"//localhost:7178/api';

  constructor(private http: HttpClient, private router: Router) {}

  getCities(){
    return this.http.get<any>(`${this.URL}/cities`);
  }

}
