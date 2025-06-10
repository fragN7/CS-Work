import {CanActivateFn, Router} from '@angular/router';
import {inject} from '@angular/core';
import {AuthService} from './authentication.service';

export const authenticationGuard: CanActivateFn = () => {
  if(inject(AuthService).isLoggedIn()){
    return true;
  }
  return inject(Router).navigateByUrl("/login");
};

export const adminGuard: CanActivateFn = () => {
  const authService = inject(AuthService);

  const isLoggedIn = authService.isLoggedIn();
  const username = localStorage.getItem('user');

  if (isLoggedIn && username === 'actis') {
    return true;
  }

  return inject(Router).navigateByUrl("/login");
};
