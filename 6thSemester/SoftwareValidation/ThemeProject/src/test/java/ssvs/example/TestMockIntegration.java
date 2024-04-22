package ssvs.example;

import domain.Nota;
import domain.Student;
import domain.Tema;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.function.Executable;
import org.mockito.Mock;
import repository.NotaXMLRepo;
import repository.StudentXMLRepo;
import repository.TemaXMLRepo;
import service.Service;
import validation.NotaValidator;
import validation.StudentValidator;
import validation.TemaValidator;
import validation.ValidationException;

import java.time.LocalDate;

import static org.mockito.Mockito.*;


public class TestMockIntegration {

    @Mock
    private StudentValidator studentValidator;

    @Mock
    private TemaValidator temaValidator;

    @Mock
    private StudentXMLRepo studentXMLRepository;

    @Mock
    private TemaXMLRepo temaXMLRepository;

    @Mock
    private NotaValidator notaValidator;

    @Mock
    private NotaXMLRepo notaXMLRepository;

    private Service service;

    @BeforeEach
    public void setup() {

        studentValidator = mock(StudentValidator.class);
        temaValidator = mock(TemaValidator.class);
        notaValidator = mock(NotaValidator.class);
        temaXMLRepository = mock(TemaXMLRepo.class);
        studentXMLRepository = mock(StudentXMLRepo.class);
        notaXMLRepository = mock(NotaXMLRepo.class);

        service = new Service(studentXMLRepository, studentValidator, temaXMLRepository, temaValidator, notaXMLRepository, notaValidator);
    }

    @Test
    public void testAddStudent(){

        Student student = new Student("", "odegaard", 933, "arsenal@ucl.com");

        try{
            doThrow(new ValidationException("Nume incorect!")).when(studentValidator).validate(student);
        }
        catch (ValidationException e){
            e.printStackTrace();
        }

        try{
            Assertions.assertThrows(ValidationException.class, () -> service.addStudent(student));
        }
        catch (ValidationException e){
            e.printStackTrace();
        }
    }

    @Test
    public void testAddStudentAndAssignment() {

        Student student = new Student("", "odegaard", 933, "arsenal@ucl.com");
        Tema tema = new Tema("2004", "", 1, 1);

        try{
            doNothing().when(studentValidator).validate(student);
            when(studentXMLRepository.save(student)).thenReturn(null);
            doThrow(new ValidationException("Descriere invalida!")).when(temaValidator).validate(tema);
        }
        catch (ValidationException e){
            e.printStackTrace();
        }

        try{
            Student studentTest = service.addStudent(student);
            Assertions.assertNull(studentTest);
            Assertions.assertThrows(ValidationException.class, () -> service.addTema(tema));
        }
        catch (ValidationException e){
            e.printStackTrace();
        }
    }


    @Test
    public void testAddStudentAndAssignmentAndGrade(){

        Student student = new Student("1111", "odegaard", 933, "arsenal@ucl.com");
        Tema tema = new Tema("1111", "a", 7, 11);
        Nota nota = new Nota("2004", "1111", "1111", 10, LocalDate.now());

        try{
            doNothing().when(studentValidator).validate(student);
            when(studentXMLRepository.save(student)).thenReturn(null);

            doNothing().when(temaValidator).validate(tema);
            when(temaXMLRepository.save(tema)).thenReturn(null);

            when(studentXMLRepository.findOne(nota.getIdStudent())).thenReturn(student);
            when(temaXMLRepository.findOne(nota.getIdTema())).thenReturn(tema);
        }
        catch (ValidationException e){
            e.printStackTrace();
        }

        try{
            Student studentTest = service.addStudent(student);
            Assertions.assertNull(studentTest);
            Tema temaTest = service.addTema(tema);
            Assertions.assertNull(temaTest);

            double notaTest = service.addNota(nota, "not ok");
            Assertions.assertEquals(7.5, notaTest);

        }
        catch (ValidationException e){
            e.printStackTrace();
        }
    }

}