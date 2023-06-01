import {RouterModule, Routes} from "@angular/router";
import {BrowseComponent} from "./browse/browse.component";
import {AddComponent} from "./add/add.component";
import {UpdateComponent} from "./update/update.component";
import {NgModule} from "@angular/core";

const routes: Routes = [
  { path: '', component: BrowseComponent },
  { path: 'add', component: AddComponent },
  { path: 'update/:id', component: UpdateComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule {}
