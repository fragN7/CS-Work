import {RouterModule, Routes} from "@angular/router";
import {LoginComponent} from "./login/login.component";
import {BrowseComponent} from "./browse/browse.component";
import {NgModule} from "@angular/core";

const routes : Routes = [
  {path: '', component: LoginComponent},
  {path: 'browse', component: BrowseComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule {}
