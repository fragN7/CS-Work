import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import {ServiceComponent} from './service/service.component';
import {AuthService} from './service/authentication/authentication.service';
import {AppComponent} from './app.component';
import {BrowserModule} from '@angular/platform-browser';
import {FormsModule, ReactiveFormsModule} from '@angular/forms';
import {AppRoutingModule} from './app.routes';
import {HttpClientModule} from '@angular/common/http';
import {LoginComponent} from './login/login.component';
import {HomeComponent} from './home/home.component';
import {WorkflowComponent} from './configuration/workflows/workflow/workflow.component';
import {
  WorkflowDeclarationComponent
} from './configuration/workflows/workflow-declaration/workflow-declaration.component';
import {CdkDropList, DragDropModule} from '@angular/cdk/drag-drop';
import {RuleComponent} from './configuration/rules/rule/rule.component';
import {PartnerComponent} from './configuration/connections/partners/partner/partner.component';
import {
  PartnerDeclarationComponent
} from './configuration/connections/partners/partner-declaration/partner-declaration.component';
import {RuleDeclarationComponent} from './configuration/rules/rule-declaration/rule-declaration.component';
import { MatSelectModule } from '@angular/material/select';
import { MatFormFieldModule } from '@angular/material/form-field';
import { MatInputModule } from '@angular/material/input';
import { MatStepperModule } from '@angular/material/stepper';
import { MatButtonModule } from '@angular/material/button';
import { MatIconModule } from '@angular/material/icon';
import {MessageDeclarationComponent} from './configuration/messages/message-declaration/message-declaration.component';
import {MessageProcessingComponent} from './configuration/messages/message-processing/message-processing.component';
import {CertificateDeclarationComponent
} from './configuration/connections/certificate-declaration/certificate-declaration.component';
import {UserComponent} from './configuration/users/user/user.component';
import {UserDeclarationComponent} from './configuration/users/user-declaration/user-declaration.component';


/*@NgModule({
  declarations: [
    LoginComponent,
    HomeComponent,
    AppComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule,
    HttpClientModule
  ],
  providers: [ServiceComponent, AuthService],
  bootstrap: [AppComponent]
})*/

@NgModule({
  declarations: [
    LoginComponent,
    HomeComponent,
    UserComponent,
    PartnerComponent,
    PartnerDeclarationComponent,
    CertificateDeclarationComponent,
    RuleComponent,
    MessageProcessingComponent,
    MessageDeclarationComponent,
    UserDeclarationComponent,
    RuleDeclarationComponent,
    WorkflowComponent,
    WorkflowDeclarationComponent,
    AppComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule,
    HttpClientModule,
    DragDropModule,
    CdkDropList,
    ReactiveFormsModule,
    MatFormFieldModule,
    MatSelectModule,
    MatInputModule,
    MatStepperModule,
    MatButtonModule,
    MatIconModule,
  ],
  providers: [ServiceComponent,AuthService],
  bootstrap: [AppComponent]
})
export class AppModule { }
