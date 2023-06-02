import {RouterModule, Routes} from "@angular/router";
import {BrowseComponent} from "./browse/browse.component";
import {AddComponent} from "./add/add.component";
import {UpdateComponent} from "./update/update.component";
import {NgModule} from "@angular/core";
import {LoginComponent} from "./login/login.component";
import {authGuard} from "./service/auth.guard";

const routes: Routes = [
  { path: 'browse', component: BrowseComponent, canActivate: [authGuard] },
  { path: 'add', component: AddComponent, canActivate: [authGuard]},
  { path: 'update/:id', component: UpdateComponent, canActivate: [authGuard] },
  { path: '', component: LoginComponent},
  { path: '**', component: LoginComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule {}
