import {RouterModule, Routes} from '@angular/router';
import {LoginComponent} from './login/login.component';
import {HomeComponent} from './home/home.component';
import {NgModule} from '@angular/core';
import {RuleComponent} from './configuration/rules/rule/rule.component';
import {WorkflowComponent} from './configuration/workflows/workflow/workflow.component';
import {WorkflowDeclarationComponent} from './configuration/workflows/workflow-declaration/workflow-declaration.component';
import {PartnerComponent} from './configuration/connections/partners/partner/partner.component';
import {
  PartnerDeclarationComponent
} from './configuration/connections/partners/partner-declaration/partner-declaration.component';
import {RuleDeclarationComponent} from './configuration/rules/rule-declaration/rule-declaration.component';
import {MessageDeclarationComponent} from './configuration/messages/message-declaration/message-declaration.component';
import {MessageProcessingComponent} from './configuration/messages/message-processing/message-processing.component';
import {
  CertificateDeclarationComponent
} from './configuration/connections/certificate-declaration/certificate-declaration.component';
import {UserComponent} from './configuration/users/user/user.component';
import {adminGuard, authenticationGuard} from './service/authentication/authentication.guard';
import {UserDeclarationComponent} from './configuration/users/user-declaration/user-declaration.component';

export const routes: Routes = [
  {path: 'login', component: LoginComponent},
  {path: '', component: HomeComponent, canActivate: [authenticationGuard]},

  {path: 'workflows', component: WorkflowComponent, canActivate: [authenticationGuard]},
  {path: 'workflow/create', component: WorkflowDeclarationComponent, canActivate: [authenticationGuard]},
  {path: 'workflow/configure/:id', component: WorkflowDeclarationComponent, canActivate: [authenticationGuard]},

  {path: 'partners', component:PartnerComponent, canActivate: [authenticationGuard]},
  {path: 'partner/create', component: PartnerDeclarationComponent, canActivate: [authenticationGuard]},
  {path: 'partner/configure/:id', component: PartnerDeclarationComponent, canActivate: [authenticationGuard]},

  {path: 'rules', component: RuleComponent, canActivate: [authenticationGuard]},
  {path: 'rule/create', component: RuleDeclarationComponent, canActivate: [authenticationGuard]},
  {path: 'rule/configure/:id', component: RuleDeclarationComponent, canActivate: [authenticationGuard]},

  {path: 'message/create', component: MessageDeclarationComponent, canActivate: [authenticationGuard]},
  {path: 'message/:id', component: MessageProcessingComponent, canActivate: [authenticationGuard]},

  {path: 'certificate/generate', component: CertificateDeclarationComponent, canActivate: [authenticationGuard]},

  {path: 'users', component: UserComponent, canActivate: [adminGuard]},
  {path: 'user/register', component: UserDeclarationComponent, canActivate: [adminGuard]}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule {}
