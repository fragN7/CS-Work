import {NgModule} from "@angular/core";
import {ServiceComponent} from "./service/service.component";
import {AddComponent} from "./add/add.component";
import {UpdateComponent} from "./update/update.component";
import {BrowseComponent} from "./browse/browse.component";
import {BrowserModule} from "@angular/platform-browser";
import {HttpClientModule} from "@angular/common/http";
import {FormsModule} from "@angular/forms";
import {AppComponent} from "./app.component";
import {AppRoutingModule} from "./app-routing.module";

@NgModule({
  declarations: [
    AppComponent,
    BrowseComponent,
    AddComponent,
    UpdateComponent,
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
export class AppModule {}
