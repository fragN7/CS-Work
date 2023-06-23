import {RouterModule, Routes} from "@angular/router";
import {LoginComponent} from "./login/login.component";
import {BrowseComponent} from "./browse/browse.component";
import {NgModule} from "@angular/core";
import {SecurityComponent} from "./security/security.component";
import {SendComponent} from "./send/send.component";

const routes : Routes = [
  {path: '', component: LoginComponent},
  {path: 'security', component: SecurityComponent},
  {path: 'browse', component: BrowseComponent},
  {path: 'send', component: SendComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule {}
