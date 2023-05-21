using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Configuration;



namespace DBMSLab2
{
    public partial class Form1 : Form
    {
        private SqlConnection conn;
        private SqlDataAdapter daParent;
        private SqlDataAdapter daChild;
        private DataSet ds;
        private List<TextBox> textBoxes;
        private BindingSource parentBindingS;
        private BindingSource childBindingS;

        public Form1()
        {
            string connectionString = ConfigurationManager.ConnectionStrings["connection_string"].ConnectionString;
            this.conn = new SqlConnection(connectionString);
            this.daParent = new SqlDataAdapter();
            this.daChild = new SqlDataAdapter();
            this.ds = new DataSet();
            this.textBoxes = new List<TextBox>();

            InitializeComponent();
            ParentTable_Load();
            LoadTextBoxes();

            this.childTable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

        }
        private void ParentTable_Load()
        {

            this.parentTable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            // We take the select command and the parentTableName
            string select = ConfigurationSettings.AppSettings["select"];
            string parentTableName = ConfigurationSettings.AppSettings["parentTableName"];

            // We create the select command
            this.daParent.SelectCommand = new SqlCommand(select, conn);

            this.ds.Clear();
            this.daParent.Fill(this.ds, parentTableName);
            this.parentTable.DataSource = this.ds.Tables[parentTableName];
        }

        private void LoadTextBoxes()
        {
            try
            {
                // We create a list of strings which contains the columnNames
                // The columnNames are splitted by ','
                List<string> ColumnNames = new List<string>(ConfigurationManager.AppSettings["ColumnNames"].Split(','));

                // We fix 2 points for X and Y, in order to place the textBoxes
                int pointX = 30;
                int pointY = 40;

                ////We take the number of columns and we clear the panel, before placing the new textBoxes
                //int numberOfColumns = Convert.ToInt32(ConfigurationManager.AppSettings["NumberOfColumns"]);
                panel.Controls.Clear();

                foreach (string columnName in ColumnNames)
                {
                    // We create a new textbox
                    TextBox a = new TextBox();
                    textBoxes.Add(a);
                    a.Text = columnName;
                    a.Name = columnName;
                    a.Location = new Point(pointX, pointY);
                    a.Visible = true;
                    a.Parent = panel;
                    panel.Show();
                    pointX += 140;
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }

        }

        private void parentTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {

            this.clearTextBoxes();

            string idTable = ConfigurationSettings.AppSettings["ID"];

            // We take the name of the foreign key
            string foreignKey = ConfigurationSettings.AppSettings["ForeignKey"];

            // We take the select command for the childTable
            string selectChild = ConfigurationSettings.AppSettings["selectChild"];

            // We take the childTable name
            string childTableName = ConfigurationSettings.AppSettings["childTableName"];

            // We take again the columnNames and split them by ','
            List<string> ColumnNames = new List<string>(ConfigurationManager.AppSettings["ColumnNames"].Split(','));

            // We take the currently selected row from the parentTable
            DataGridViewRow selectedParent = this.parentTable.SelectedRows[0];

            // We go through our textBoxes and look for the one with the name as the foreign key, and we populate it with the value of the foreign key
            foreach (TextBox tb in textBoxes)
            {
                if (tb.Name == foreignKey)
                {
                    tb.Text = selectedParent.Cells[0].Value.ToString();
                }
            }

            // We check if there is anything selected
            if (this.parentTable.SelectedRows.Count > 0)
            {
                // We take the value of the id from the selected row
                string id = selectedParent.Cells[idTable].Value.ToString();

                // We create the select command
                this.daChild.SelectCommand = new SqlCommand(selectChild + id, this.conn);

                this.ds = new DataSet();
                this.daChild.Fill(this.ds, childTableName);
                this.childTable.DataSource = this.ds.Tables[childTableName];

            }


        }

        private void childTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {

            // We take the index of the first selected row form the child table
            int index = this.childTable.SelectedRows[0].Index;

            string childTableName = ConfigurationSettings.AppSettings["ChildTableName"];

            for (int i = 0; i < this.textBoxes.Count; i++)
            {
                this.textBoxes[i].Text = this.ds.Tables[childTableName].Rows[index][i].ToString();
            }
        }

        public void clearTextBoxes()
        {
            // Like that we clear the contend form the textBoxes
            foreach (TextBox tb in textBoxes)
            {
                tb.Clear();
            }
        }

        private void insertButton_Click(object sender, EventArgs e)
        {
            try
            {
                // We take the insert command
                string insertCommand = ConfigurationSettings.AppSettings["InsertQuery"];

                // We create the insert command
                this.daChild.InsertCommand = new SqlCommand(insertCommand, this.conn);

                // We take the childTable's name
                string childTableName = ConfigurationManager.AppSettings["ChildTableName"];

                // We create a list with the column names of the child table which are splited by ','

                List<string> columnNamesList = new List<string>(ConfigurationManager.AppSettings["ColumnNames"].Split(','));

                // We go throguh all these columnNames
                // And then we parse the list of textBoxes in order to find the one whose name is the same as the columnName 
                foreach (string columnName in columnNamesList)
                {
                    foreach (TextBox tb in this.textBoxes)
                    {
                        if (tb.Name == columnName)
                        {
                            // After we find it, we insert to the coresponding parameter, the text from the textBox 
                            this.daChild.InsertCommand.Parameters.AddWithValue("@" + columnName, tb.Text);
                        }
                    }
                }

                // We open the connection and execute the query
                this.conn.Open();
                this.daChild.InsertCommand.ExecuteNonQuery();
                this.conn.Close();

                MessageBox.Show("Inserted with succes!");

                // We update the child table
                this.ds = new DataSet();
                this.daChild.Fill(this.ds, childTableName);
                this.childTable.DataSource = this.ds.Tables[childTableName];

                this.clearTextBoxes();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.conn.Close();
            }

        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            DialogResult dr;
            dr = MessageBox.Show("Are you sure?\n No undo after delete!", "Confirm Deletion", MessageBoxButtons.YesNo);
            if (dr == DialogResult.Yes)
            {
                try
                {
                    string id = ConfigurationManager.AppSettings["idChild"];

                    string deleteCommand = ConfigurationManager.AppSettings["DeleteQuery"];

                    this.daChild.DeleteCommand = new SqlCommand(deleteCommand, this.conn);

                    // We take the childTable's name
                    string childTableName = ConfigurationManager.AppSettings["ChildTableName"];

                    // We create a list with the column names of the child table which are splited by ','
                    List<string> columnNamesList = new List<string>(ConfigurationManager.AppSettings["ColumnNames"].Split(','));

                    // We go throguh all these columnNames
                    // And then we parse the list of textBoxes in order to find the one whose name is the same as the columnName 

                    foreach (TextBox tb in this.textBoxes)
                    {
                        if (tb.Name == id)
                        {
                            // After we find it, we insert to the coresponding parameter, the text from the textBox 
                            this.daChild.DeleteCommand.Parameters.AddWithValue("@" + id, tb.Text);
                        }
                        break;
                    }


                    this.conn.Open();
                    this.daChild.DeleteCommand.ExecuteNonQuery();
                    this.conn.Close();

                    MessageBox.Show("Deleted with success!");

                    // We update the child table
                    this.ds = new DataSet();
                    this.daChild.Fill(this.ds, childTableName);
                    this.childTable.DataSource = this.ds.Tables[childTableName];

                    this.clearTextBoxes();

                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                MessageBox.Show("Deletion Aborted");
                this.conn.Close();
            }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            try
            {
                string updateCommand = ConfigurationManager.AppSettings["UpdateQuery"];

                this.daChild.UpdateCommand = new SqlCommand(updateCommand, this.conn);

                // We take the childTable's name
                string childTableName = ConfigurationManager.AppSettings["ChildTableName"];

                // We create a list with the column names of the child table which are splited by ','
                List<string> columnNamesList = new List<string>(ConfigurationManager.AppSettings["ColumnNames"].Split(','));

                // We go throguh all these columnNames
                // And then we parse the list of textBoxes in order to find the one whose name is the same as the columnName 
                foreach (string columnName in columnNamesList)
                {
                    foreach (TextBox tb in this.textBoxes)
                    {
                        if (tb.Name == columnName)
                        {
                            // After we find it, we insert to the coresponding parameter, the text from the textBox 
                            this.daChild.UpdateCommand.Parameters.AddWithValue("@" + columnName, tb.Text);
                        }
                    }
                }

                // We open the connection and execute the query
                this.conn.Open();
                this.daChild.UpdateCommand.ExecuteNonQuery();
                this.conn.Close();
                MessageBox.Show("Updated with succes!");

                // We update the child table
                this.ds = new DataSet();
                this.daChild.Fill(this.ds, childTableName);
                this.childTable.DataSource = this.ds.Tables[childTableName];

                this.clearTextBoxes();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.conn.Close();
            }
        }
    }

}