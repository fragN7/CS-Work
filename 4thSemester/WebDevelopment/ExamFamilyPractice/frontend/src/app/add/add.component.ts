import { Component } from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-add',
  templateUrl: './add.component.html',
  styleUrls: ['./add.component.css']
})
export class AddComponent {
  family = {
    mother: '',
    father: ''
  }
  constructor(private service: ServiceComponent, private router: Router) {}

  add(){
    this.service.add(this.family.mother, this.family.father).subscribe(
      (response: any) => {
        alert('Added');
      },
      (error: any) => {
        alert(error.error);
      })
  }
}
