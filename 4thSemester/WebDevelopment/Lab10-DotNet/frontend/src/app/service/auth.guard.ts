import {CanActivateFn, Router} from '@angular/router';
import {inject} from "@angular/core";
import {AuthService} from "./auth.service";

export const authGuard: CanActivateFn = () => {
  if(inject(AuthService).isLoggedIn()){
    return true;
  }
  return inject(Router).navigateByUrl("/");
};
