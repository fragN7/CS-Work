import {RouterModule, Routes} from "@angular/router";
import {BrowseComponent} from "./browse/browse.component";
import {NgModule} from "@angular/core";

const routes : Routes = [
  {path: '', component: BrowseComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule {}
