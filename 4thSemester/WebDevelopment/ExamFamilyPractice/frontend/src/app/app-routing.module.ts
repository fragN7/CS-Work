import {RouterModule, Routes} from "@angular/router";
import {LoginComponent} from "./login/login.component";
import {BrowseComponent} from "./browse/browse.component";
import {AddComponent} from "./add/add.component";
import {NgModule} from "@angular/core";

const routes : Routes = [
  {path: '', component: LoginComponent},
  {path: 'browse', component: BrowseComponent},
  {path: 'add', component: AddComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule {}
