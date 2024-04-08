package ssvs.example;

import domain.Nota;
import domain.Student;
import domain.Tema;
import org.junit.jupiter.api.Test;
import repository.NotaXMLRepo;
import repository.StudentXMLRepo;
import repository.TemaXMLRepo;
import service.Service;
import validation.NotaValidator;
import validation.StudentValidator;
import validation.TemaValidator;

import java.io.File;
import java.time.LocalDate;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

public class TestIntegration {
    private Service service;

    @Test
    public void testAddStudent() {

        StudentValidator studentValidator = new StudentValidator();
        TemaValidator temaValidator = new TemaValidator();

        StudentXMLRepo studentXMLRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        TemaXMLRepo temaXMLRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        NotaValidator notaValidator = new NotaValidator(studentXMLRepository, temaXMLRepository);
        NotaXMLRepo notaXMLRepository = new NotaXMLRepo("fisiere/noteTest.xml");
        this.service = new Service(studentXMLRepository, studentValidator, temaXMLRepository, temaValidator, notaXMLRepository, notaValidator);

        Student student = new Student("8", "Odegaard", 933, "odegaard@arsenal.com");
        assertNull(service.addStudent(student));

        //this.service.deleteStudent("8");
    }

    @Test
    public void testAddTema() {

        StudentValidator studentValidator = new StudentValidator();
        TemaValidator temaValidator = new TemaValidator();

        StudentXMLRepo studentXMLRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        TemaXMLRepo temaXMLRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        NotaValidator notaValidator = new NotaValidator(studentXMLRepository, temaXMLRepository);
        NotaXMLRepo notaXMLRepository = new NotaXMLRepo("fisiere/noteTest.xml");
        this.service = new Service(studentXMLRepository, studentValidator, temaXMLRepository, temaValidator, notaXMLRepository, notaValidator);

        Tema tema = new Tema("14", "Thierry Henry", 5, 12);
        assertNull(this.service.addTema(tema));

        //this.service.deleteTema("14");
    }

    @Test
    public void testAddGrade() {

        StudentValidator studentValidator = new StudentValidator();
        TemaValidator temaValidator = new TemaValidator();

        StudentXMLRepo studentXMLRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        TemaXMLRepo temaXMLRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        NotaValidator notaValidator = new NotaValidator(studentXMLRepository, temaXMLRepository);
        NotaXMLRepo notaXMLRepository = new NotaXMLRepo("fisiere/noteTest.xml");
        this.service = new Service(studentXMLRepository, studentValidator, temaXMLRepository, temaValidator, notaXMLRepository, notaValidator);

        Nota nota = new Nota("1", "8", "14", 10, LocalDate.now());
        assertEquals(this.service.addNota(nota, "COYG"), 7.5);

        this.service.deleteNota("1");
        this.service.deleteStudent("8");
        this.service.deleteTema("14");
    }

    @Test
    public void testAddStudentTemaGrade() {

        StudentValidator studentValidator = new StudentValidator();
        TemaValidator temaValidator = new TemaValidator();

        StudentXMLRepo studentXMLRepository = new StudentXMLRepo("fisiere/studentiTest.xml");
        TemaXMLRepo temaXMLRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        NotaValidator notaValidator = new NotaValidator(studentXMLRepository, temaXMLRepository);
        NotaXMLRepo notaXMLRepository = new NotaXMLRepo("fisiere/noteTest.xml");
        this.service = new Service(studentXMLRepository, studentValidator, temaXMLRepository, temaValidator, notaXMLRepository, notaValidator);

        Student student = new Student("10", "Odegaard", 933, "odegaard@ucl.com");
        Tema tema = new Tema("10", "Thierry Henry", 5, 12);
        Nota nota = new Nota("10", "10", "10", 10, LocalDate.now());

        assertNull(this.service.addStudent(student));
        assertNull(this.service.addTema(tema));
        assertEquals(this.service.addNota(nota, "COYG"), 7.5);

        this.service.deleteNota("10");
        this.service.deleteStudent("10");
        this.service.deleteTema("10");
    }

}
