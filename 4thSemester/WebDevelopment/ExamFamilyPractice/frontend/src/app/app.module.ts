import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { AddComponent } from './add/add.component';
import { LoginComponent } from './login/login.component';
import { BrowseComponent } from './browse/browse.component';
import {AppRoutingModule} from "./app-routing.module";
import {FormsModule} from "@angular/forms";
import {HttpClientModule} from "@angular/common/http";
import {ServiceComponent} from "./service/service.component";

@NgModule({
  declarations: [
    AppComponent,
    AddComponent,
    LoginComponent,
    BrowseComponent,
    ServiceComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    HttpClientModule
  ],
  providers: [ServiceComponent],
  bootstrap: [AppComponent]
})
export class AppModule { }
