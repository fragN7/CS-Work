import { ComponentFixture, TestBed } from '@angular/core/testing';

import { WorkflowDeclarationComponent } from './workflow-declaration.component';

describe('WorkflowDeclarationComponent', () => {
  let component: WorkflowDeclarationComponent;
  let fixture: ComponentFixture<WorkflowDeclarationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [WorkflowDeclarationComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(WorkflowDeclarationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
