import {Component, Injectable, OnInit} from '@angular/core';
import {HttpClient, HttpHeaders, HttpParams} from '@angular/common/http';
import {Router} from '@angular/router';
import {interval, Observable, Subscription, switchMap, tap} from 'rxjs';

export interface Channel{
  id: string,
  rules: Rule[],
  partnerId: string,
  partner: Partner
}

export interface Partner{
  id: string,
  name: string,
  ipAddress: string,
  certificate: string,
  communicationChannelId?: string
}

export interface CommunicationChannel{
  id: string,
  rules: Rule[],
  partnerId: string
}

export interface WorkflowStep{
  id: string,
  name: string,
  filePath?: string,
  command?: string,
  file?: File
}

export interface Workflow{
  id: string,
  name: string,
  workflowSteps: WorkflowStep[]
}

export interface Rule {
  id: string,
  sender: string,
  objectType: string;
  receiver: string;
  timeStamp: string;
  workflowId: string;
  workflow: Workflow;
}

export interface MessageStep {
  id: string,
  stepName: string,
  startedTime: string,
  endedTime: string,
  result: string,
  filePath: File
}

export interface User{
  id: string,
  userName: string,
  password: string
}

export interface Message {
  id: string,
  timeStamp: string,
  rule: Rule,
  messageSteps: MessageStep[],
  user: User;
}

@Injectable({
  providedIn: 'root'
})
export class ServiceComponent implements OnInit{

  private URL = localStorage.getItem('myURL');
  private pollingSubscription!: Subscription;
  statusMessage = 'Checking...';
  constructor(private http: HttpClient, private router: Router) {}

  ngOnInit(): void {
    console.log("started");
    this.pollingSubscription = interval(10000)
      .pipe(switchMap(() => this.checkForFiles()))
      .subscribe({
        next: (data) => {
          this.statusMessage = `${data.message} (${data.count ?? 0})`;
          console.log(data.count);
        },
        error: (err) => {
          this.statusMessage = 'Error checking folder.';
          console.error(err);
        }
      });
  }

  checkForFiles(): Observable<any> {
    return this.http.get<any[]>(`${this.URL}/Message/messages/out/check`);
  }

  /*

      MESSAGES
        -getMessages
        -getMessageById
        -addMessage
        -processMessage
        -deleteMessage
        -assignMessageToUser
        -getFileFromPath

  */
  getMessages(){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    const defaultValue = '*';

    return this.http.get<any[]>(`${this.URL}/Message/messages/${defaultValue}`, {headers});
  }

  getMessageById(id: string){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.get<any>(`${this.URL}/Message/message/${id}`, {headers});
  }

  addMessage(rule: Rule, file: File) {

    const body = new FormData();
    body.append('file', file);
    body.append('ruleId', rule.id);

      const token = localStorage.getItem('token');
      const headers = new HttpHeaders()
        .append('Authorization', `Bearer ${token}`);

      this.http.post<any>(`${this.URL}/Message/message/store`, body, {headers}).pipe(
        tap(() => {
        })
      ).subscribe(
        response => {
          console.log("Message added successfully", response);
          this.router.navigateByUrl("/")
        },
        error => {
          console.error("Error while adding message", error);
        }
      );
  }

  restartMessage(rule: Rule, filePath: string) {

    const body = new FormData();
    body.append('filePath', filePath);
    body.append('ruleId', rule.id);

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`);

    this.http.post<any>(`${this.URL}/Message/message/restart`, body, {headers}).pipe(
      tap(() => {
      })
    ).subscribe(
      response => {
        console.log("Message restarted successfully", response);
        this.router.navigateByUrl("/")
      },
      error => {
        console.error("Error while restarting message", error);
      }
    );
  }

  processMessage(filePath: string, fileName: string, id: string, step: string){

    const body = new FormData();
    body.append('filePath', filePath);
    body.append('fileName', fileName);
    body.append('step', step);

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`);

    this.http.put<any>(`${this.URL}/Message/message/process/step/${id}`, body, {headers}).pipe(
      tap(() => {
      })
    ).subscribe(
      response => {
        console.log("Step processed successfully", response);
        this.router.navigateByUrl("/")
      },
      error => {
        console.error("Error while processing step", error);
      }
    );
  }

  deleteMessage(id: string){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.delete<any>(`${this.URL}/Message/message/delete/${id}`, {headers});
  }

  assignMessageToUser(messageId: string, id: string){
    const body = {
      'messageId': messageId
    };

    console.log(body);
    console.log(id);

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.put<any>(`${this.URL}/Message/message/user/assign/${id}`, body, { headers }).pipe(
      tap(() => {
      })
    ).subscribe(
      response => {
        console.log("Assigned message", response);
        window.location.reload();
      },
      error => {
        console.error("Error while assigning message", error);
      }
    );
  }

  getFileContentFromPath(filePath: string){

    const body = {
      'filePath': filePath
    }

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.post<any>(`${this.URL}/Message/message/step/file`, body, {headers, responseType: 'text' as 'json'}) as Observable<string>;
  }


  /*

      WORKFLOWS
        -getWorkflows
        -getWorkflowById
        -addWorkflow
        -editWorkflow
        -deleteWorkflow

  */


  getWorkflows(){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    const defaultValue = '*';
    return this.http.get<any[]>(`${this.URL}/Workflow/workflows/${defaultValue}`, {headers});
  }

  getWorkflowById(workflowId: string){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.get<any>(`${this.URL}/Workflow/workflow/${workflowId}`, {headers});
  }

  addWorkflow(name: string, steps: WorkflowStep[]){
    const formData = new FormData();
    formData.append('name', name);
    steps.forEach((step, index) => {
      formData.append(`workflowSteps[${index}].id`, step.id);
      formData.append(`workflowSteps[${index}].name`, step.name);
      formData.append(`workflowSteps[${index}].filePath`, step.filePath || 'x');
      formData.append(`workflowSteps[${index}].command`, step.command || 'x');
      formData.append(`workflowSteps[${index}].file`, step.file || new Blob([]), step.file?.name || 'x');
    });

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Access-Control-Allow-Origin', '*');

    this.http.post<any>(`${this.URL}/Workflow/workflow/add`, formData, { headers }).pipe(
      tap(() => {
      })
    ).subscribe(
      response => {
        console.log("Workflow added successfully", response);
        this.router.navigateByUrl("/workflows");
      },
      error => {
        console.error("Error while adding workflow", error.error);

        let rawError = error.error;
        let message = '';

        if (typeof rawError === 'string') {
          const match = rawError.match(/System\.Exception:\s*(.*)/);
          if (match && match[1]) {
            message = match[1].split('\n')[0].trim();
          } else {
            message = rawError.split('\n')[0].trim();
          }
        } else {
          message = 'An unknown error occurred.';
        }

        alert(`Error while adding workflow":\n${message}`);
      }
    );
  }

  editWorkflow(id: string, name: string){
    const formData = new FormData();
    formData.append('name', name);

    console.log(formData);

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`);

    return this.http.put<any>(`${this.URL}/Workflow/workflow/update/${id}`, formData, { headers }).pipe(
      tap(() => {
      })
    ).subscribe(
      response => {
        console.log("Workflow updated successfully", response);
        this.router.navigateByUrl("/workflows");

      },
      error => {
        console.error("Error while updating workflow", error.error);

        let rawError = error.error;
        let message = '';

        if (typeof rawError === 'string') {
          const match = rawError.match(/System\.Exception:\s*(.*)/);
          if (match && match[1]) {
            message = match[1].split('\n')[0].trim();
          } else {
            message = rawError.split('\n')[0].trim();
          }
        } else {
          message = 'An unknown error occurred.';
        }

        alert(`Error while updating workflow":\n${message}`);
      }
    );
  }

  deleteWorkflow(id: string){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.delete<any>(`${this.URL}/Workflow/workflow/delete/${id}`, {headers});
  }

  /*

      RULES
        -getRules
        -getRuleById
        -addRule
        -editRule
        -deleteRule

  */

  getRules(){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    const defaultValue = '*';
    return this.http.get<any[]>(`${this.URL}/Rule/rules/${defaultValue}/${defaultValue}/${defaultValue}/${defaultValue}/${defaultValue}`, {headers});
  }

  getRuleById(ruleId: string){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.get<any>(`${this.URL}/Rule/rule/${ruleId}`, {headers});
  }

  addRule(sender: string, objectType: string, receiver: string, timeStamp: string, workflowId: string){
    const body = {
      'sender' : sender,
      'objectType' : objectType,
      'receiver' : receiver,
      'timeStamp' : timeStamp,
      'workflowId' : workflowId
    }

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    this.http.post<any>(`${this.URL}/Rule/rule/add`, body, { headers }).pipe(
      tap(() => {
      })
    ).subscribe(
      response => {
        console.log("Rule added successfully", response);
        this.router.navigateByUrl("/rules");
      },
      error => {
        console.error("Error while adding rule", error.error);

        let rawError = error.error;
        let message = '';

        if (typeof rawError === 'string') {
          const match = rawError.match(/System\.Exception:\s*(.*)/);
          if (match && match[1]) {
            message = match[1].split('\n')[0].trim();
          } else {
            message = rawError.split('\n')[0].trim();
          }
        } else {
          message = 'An unknown error occurred.';
        }

        alert(`Error while adding rule":\n${message}`);
      }
    );
  }

  editRule(ruleId: string, workflowId: string, timeStamp: string){
    const body = {
      'workflowId' : workflowId,
      'timeStamp' : timeStamp
    }

    console.log(body);

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.put<any>(`${this.URL}/Rule/rule/update/${ruleId}`, body, { headers }).pipe(
      tap(() => {
      })
    ).subscribe(
      response => {
        console.log("Rule updated successfully", response);
        this.router.navigateByUrl("/rules");
      },
      error => {
        console.error("Error while updating rule", error.error);

        let rawError = error.error;
        let message = '';

        if (typeof rawError === 'string') {
          const match = rawError.match(/System\.Exception:\s*(.*)/);
          if (match && match[1]) {
            message = match[1].split('\n')[0].trim();
          } else {
            message = rawError.split('\n')[0].trim();
          }
        } else {
          message = 'An unknown error occurred.';
        }

        alert(`Error while updating rule":\n${message}`);
      }
    );
  }

  deleteRule(id: string){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.delete<any>(`${this.URL}/Rule/rule/delete/${id}`, {headers});
  }

  /*

      PARTNERS
        -getPartners
        -getPartnerById
        -addPartner
        -editPartner
        -deletePartner

  */

  getPartners(){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    const defaultValue = '*';
    return this.http.get<any[]>(`${this.URL}/Partner/partners/${defaultValue}/${defaultValue}/${defaultValue}`, {headers});
  }

  getPartnerById(partnerId: string){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.get<any>(`${this.URL}/Partner/partners/${partnerId}`, {headers});
  }

  addPartner(name: string, ipAddress: string, certificate: string, certificateFile: File){
    const formData = new FormData();
    formData.append('name', name);
    formData.append('ipAddress', ipAddress);
    formData.append('certificate', certificate);
    formData.append('certificateFile', certificateFile);

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`);

    return this.http.post<any>(`${this.URL}/Partner/partner/add`, formData, { headers });
  }

  editPartner(id: string, name: string, ipAddress: string, certificate: string, certificateFile: File){
    const formData = new FormData();
    formData.append('name', name);
    formData.append('ipAddress', ipAddress);
    formData.append('certificate', certificate);
    formData.append('certificateFile', certificateFile);

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`);

    return this.http.put<any>(`${this.URL}/Partner/partner/update/${id}`, formData, { headers }).pipe(
      tap(() => {
      })
    ).subscribe(
      response => {
        console.log("Partner updated successfully", response);
        this.router.navigateByUrl("/partners");
      },
      error => {
        console.error("Error while adding partner", error.error);

        let rawError = error.error;
        let message = '';

        if (typeof rawError === 'string') {
          const match = rawError.match(/System\.Exception:\s*(.*)/);
          if (match && match[1]) {
            message = match[1].split('\n')[0].trim();
          } else {
            message = rawError.split('\n')[0].trim();
          }
        } else {
          message = 'An unknown error occurred.';
        }

        alert(`Error while adding partner:\n${message}`);
      }
    );
  }

  deletePartner(id: string){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.delete<any>(`${this.URL}/Partner/partner/delete/${id}`, {headers});
  }

  /*

      COMMUNICATION CHANNEL
        -addChannel
        -deleteChannel

  */
  addChannel(partnerId: string){
    const body = {
      'id' : partnerId,
      'partnerId' : partnerId
    }

    console.log(body);

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    this.http.post<any>(`${this.URL}/CommunicationChannel/channel/add`, body, { headers }).pipe(
      tap(() => {
      })
    ).subscribe(
      response => {
        console.log("Channel added successfully", response);
      },
      error => {
        console.error("Error while adding channel", error);
      }
    );
  }

  deleteChannel(id: string){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.delete<any>(`${this.URL}/CommunicationChannel/channel/delete/${id}`, {headers});
  }

  /*
      CERTIFICATE
        -generateCertificate
  */

  generateCertificate(sender: string, receiver: string, standard: string, hostName: string, port: string){
    const userId = localStorage.getItem('userId');
    const body = {
      'sender' : sender,
      'receiver' : receiver,
      'standard' : standard,
      'hostName' : hostName,
      'port' : port.toString()
    }

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.post<any>(`${this.URL}/Certificate/certificate/create/${userId}`, body, {headers});
  }

  /*
    USERS
      -getUsers
      -registerUser
      -deleteUser
  */

  getUsers(){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    const defaultValue = '*';

    return this.http.get<any[]>(`${this.URL}/Authentication/users`, {headers});
  }

  registerUser(userName: string, password: string): Observable<any> {
    const user = {
      userName: userName,
      password: password
    };

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.post<any>(`${this.URL}/Authentication/register`, user, {headers});
  }

  deleteUser(id: string){
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.delete<any>(`${this.URL}/Authentication/delete/${id}`, {headers});
  }
}
