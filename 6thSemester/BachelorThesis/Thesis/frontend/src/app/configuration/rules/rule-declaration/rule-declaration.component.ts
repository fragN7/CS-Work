import {Component, OnDestroy, OnInit} from '@angular/core';
import {Partner, Rule, ServiceComponent, Workflow} from '../../../service/service.component';
import {AuthService} from '../../../service/authentication/authentication.service';
import {Router} from '@angular/router';
import {CdkDragDrop, moveItemInArray, transferArrayItem} from '@angular/cdk/drag-drop';
import {FormBuilder, FormGroup, Validators} from '@angular/forms';

@Component({
  selector: 'app-rule-declaration',
  standalone: false,
  templateUrl: './rule-declaration.component.html',
  styleUrl: './rule-declaration.component.css'
})
export class RuleDeclarationComponent implements OnInit, OnDestroy{

  rule: Rule = { id: '', sender: '',  objectType: '', receiver: '', timeStamp: '', workflowId: '', workflow: {} as Workflow};
  partners: Partner[] = [];
  workflows: Workflow[] = [];
  timeStamps: string[] = ["BANKTEST", "DEFAULTS"];
  username?: string = '';
  isEditMode = false;

  senderForm: FormGroup;
  objectTypeForm: FormGroup;
  receiverForm: FormGroup;
  timeStampForm: FormGroup;
  workflowForm: FormGroup;
  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router, private fb: FormBuilder) {
    this.senderForm = this.fb.group({
      sender: ['', Validators.required]
    });

    this.objectTypeForm = this.fb.group({
      objectType: ['', Validators.required]
    });

    this.receiverForm = this.fb.group({
      receiver: ['', Validators.required]
    });

    this.timeStampForm = this.fb.group({
      timeStamp: ['', Validators.required]
    });


    this.workflowForm = this.fb.group({
      workflow: [null, Validators.required]
    });
  }

  ngOnInit() {

    const ruleId = localStorage.getItem('ruleId')?.toString();
    const saveType = localStorage.getItem('saveType');
    this.isEditMode = saveType === 'edit';
    if(ruleId != null){
      this.getRuleById(ruleId);
    }

    this.service.getPartners().subscribe(
      (response: Partner[]) => {
        this.partners = response;
      },
      (error: any) => {
        console.error('Error fetching partners: ', error);
      }
    )

    this.service.getWorkflows().subscribe(
      (response: Workflow[]) => {
        this.workflows = response;
      },
      (error: any) => {
        console.error('Error fetching workflows: ', error);
      }
    )

    this.username = localStorage.getItem('user')?.toString();

    this.senderForm.get('sender')?.valueChanges.subscribe(val => this.rule.sender = val);
    this.objectTypeForm.get('objectType')?.valueChanges.subscribe(val => this.rule.objectType = val);
    this.receiverForm.get('receiver')?.valueChanges.subscribe(val => this.rule.receiver = val);
    this.timeStampForm.get('timeStamp')?.valueChanges.subscribe(val => this.rule.timeStamp = val);
    this.workflowForm.get('workflow')?.valueChanges.subscribe(val => this.rule.workflow = val);
  }

  allFormsValid(): boolean {
    return this.timeStampForm.valid &&
           this.workflowForm.valid;
  }

  ngOnDestroy() {
    localStorage.removeItem('ruleId');
    localStorage.removeItem('saveType');
  }

  getRuleById(ruleId: string){
    this.service.getRuleById(ruleId).subscribe(
      (response: Rule) => {
        this.rule = response;

        this.senderForm.patchValue({ sender: response.sender });
        this.objectTypeForm.patchValue({ objectType: response.objectType });
        this.receiverForm.patchValue({ receiver: response.receiver });
        this.timeStampForm.patchValue({ timeStamp: response.timeStamp });
        this.workflowForm.patchValue({ workflow: response.workflow });

        const saveType = localStorage.getItem('saveType');
        if (saveType === 'edit') {
          // Disable all except workflowForm
          this.senderForm.disable();
          this.objectTypeForm.disable();
          this.receiverForm.disable();

          // Make sure workflowForm is enabled so user can edit it

          this.timeStampForm.enable();
          this.workflowForm.enable();
        }
      },
      (error: any) => {
        console.error('Error fetching rule: ', error);
      }
    )
  }

  userLogout(){
    this.userService.logout();
  }

  saveRule() {

    const type = localStorage.getItem('saveType');


    if(type == 'edit'){
      this.service.editRule(localStorage.getItem('ruleId')!, this.rule.workflow.id, this.rule.timeStamp);
    } else {
      this.service.addRule(this.rule.sender, this.rule.objectType, this.rule.receiver, this.rule.timeStamp, this.rule.workflow.id);
    }
  }

}
