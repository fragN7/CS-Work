import {RouterModule, Routes} from "@angular/router";
import {BrowseComponent} from "./browse/browse.component";
import {NgModule} from "@angular/core";
import {RouteComponent} from "./route/route.component";

const routes : Routes = [
  {path: '', component: BrowseComponent},
  {path: 'route', component: RouteComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule {}
