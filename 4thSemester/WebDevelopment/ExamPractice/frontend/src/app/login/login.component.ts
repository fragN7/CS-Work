import { Component } from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {

  authors = {
    firstAuthor: '',
    secondAuthor: ''
  }

  constructor(private service: ServiceComponent, private router: Router) {}

  login(){
    const error = this.validateForm();
    if(error != ''){
      alert(error);
      return;
    }

    console.log(this.authors.firstAuthor);

    this.service.getBooksArticles(this.authors.firstAuthor, this.authors.secondAuthor).subscribe(data => {
      localStorage.setItem('firstAuthor', this.authors.firstAuthor);
      localStorage.setItem('secondAuthor', this.authors.secondAuthor);
      this.router.navigateByUrl("/browse");
    }, (error: any) => {
      alert(error.error);
    });
  }

  validateForm(){
    const {firstAuthor, secondAuthor} = this.authors;
    let errors = '';

    if(!firstAuthor && !secondAuthor){
      errors += 'Please enter at least one author name.';
    }

    return errors;
  }
}
