package ssvs.example;

import domain.Tema;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import repository.StudentXMLRepo;
import repository.TemaXMLRepo;
import service.Service;
import validation.StudentValidator;
import validation.TemaValidator;
import validation.ValidationException;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestAddTema {

    private TemaXMLRepo temaFileRepository;
    private TemaValidator temaValidator;
    private Service service;

    /*@BeforeAll
    static void createXML() {
        File xml = new File("fisiere/temeTest.xml");
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(xml))) {
            writer.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n" +
                    "<inbox>\n" +
                    "\n" +
                    "</inbox>");
            writer.flush();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    @BeforeEach
    public void setup() {
        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);
    }

    @AfterAll
    static void removeXML() {
        new File("fisiere/temeTest.xml").delete();
    }*/

    @Test
    void testAddAssignmentValidAssignment() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema("1", "SVSS", 1, 1);
        this.service.addTema(newTema);

        java.util.Iterator<Tema> assignments = this.service.getAllTeme().iterator();
        assertEquals(assignments.next().getID(), newTema.getID());
    }

    @Test
    void testAddAssignmentEmptyID() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema("", "SVSS", 1, 1);
        assertThrows(ValidationException.class, () -> this.service.addTema(newTema));
    }

    @Test
    void testAddAssignmentNullID() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema(null, "SVSS", 1, 1);
        assertThrows(java.lang.NullPointerException.class, () -> this.service.addTema(newTema));
    }

    @Test
    void testAddAssignmentEmptyDescription() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema("1", "", 1, 1);
        assertThrows(ValidationException.class, () -> this.service.addTema(newTema));
    }

    @Test
    void testAddAssignmentDeadlineTooLarge() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema("1", "SVSS", 15, 1);
        assertThrows(ValidationException.class, () -> this.service.addTema(newTema));
    }

    @Test
    void testAddAssignmentDeadlineTooSmall() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema("1", "SVSS", 0, 1);
        assertThrows(ValidationException.class, () -> this.service.addTema(newTema));
    }

    @Test
    void testAddAssignmentReceivedTooSmall() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema("1", "SVSS", 1, 0);
        assertThrows(ValidationException.class, () -> this.service.addTema(newTema));
    }

    @Test
    void testAddAssignmentReceivedTooLarge() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema("1", "SVSS", 1, 15);
        assertThrows(ValidationException.class, () -> this.service.addTema(newTema));
    }

    @Test
    void testAddAssignmentDuplicateAssignment() {

        this.temaFileRepository = new TemaXMLRepo("fisiere/temeTest.xml");
        this.temaValidator = new TemaValidator();
        this.service = new Service(null, null, this.temaFileRepository, this.temaValidator, null, null);

        Tema newTema = new Tema("1", "SVSS", 1, 1);
        this.service.addTema(newTema);

        Tema newTema2 = new Tema("1", "SVSS", 1, 1);

        assertEquals(this.service.addTema(newTema2).getID(), newTema.getID());
    }
}
