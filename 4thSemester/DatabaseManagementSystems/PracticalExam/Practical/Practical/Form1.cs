using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Practical
{
    public partial class Form1 : Form
    {
        private SqlConnection connectionString;
        private SqlDataAdapter da;
        private DataSet ds;

        public Form1()
        {
            this.connectionString = new SqlConnection(GetConnectionString());
            this.da = new SqlDataAdapter();
            this.ds = new DataSet();

            InitializeComponent();
            this.sportIDBox.ReadOnly = true;
            this.dgvPlayers.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            parentTable_load();
        }

        private void button1_click(object sender, EventArgs e)
        {

        }

        private void childTable_load()
        {

        }

        private void parentTable_load()
        {
            this.dgvSports.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            this.da.SelectCommand = new SqlCommand("select * from Sports", connectionString);
            this.ds.Clear();
            this.da.Fill(this.ds, "Sports");

            this.dgvSports.DataSource = this.ds.Tables["Sports"];
        }

        private void form1_load(object sender, EventArgs e)
        {

        }

        private void clearTextBoxes()
        {
            this.pidBox.Clear();
            this.nameBox.Clear();
            this.surnameBox.Clear();
            this.dateBox.Clear(); 
            this.genderBox.Clear();
            this.sportIDBox.Clear();
        }

        private void parentTable_click(object sender, DataGridViewCellEventArgs e)
        {
            this.clearTextBoxes();
            DataGridViewRow selectedParent = this.dgvSports.SelectedRows[0];
            this.sportIDBox.Text = selectedParent.Cells[0].Value.ToString();

            if(this.dgvSports.SelectedRows.Count > 0)
            {
                int sportID = Convert.ToInt32(selectedParent.Cells[0].Value);

                this.da.SelectCommand = new SqlCommand("select * from Players where sport_id = @id", this.connectionString);
                this.da.SelectCommand.Parameters.AddWithValue("@id", sportID);

                this.ds = new DataSet();
                this.da.Fill(this.ds, "Players");
                this.dgvPlayers.DataSource = this.ds.Tables["Players"];
            }
        }

        private void childTable_click(Object sender, DataGridViewCellEventArgs e)
        {
            int index = this.dgvPlayers.SelectedRows[0].Index;

            this.pidBox.Text = this.ds.Tables["Players"].Rows[index][0].ToString();
            this.nameBox.Text = this.ds.Tables["Players"].Rows[index][2].ToString();
            this.surnameBox.Text = this.ds.Tables["Players"].Rows[index][3].ToString();
            this.dateBox.Text = this.ds.Tables["Players"].Rows[index][4].ToString();
            this.genderBox.Text = this.ds.Tables["Players"].Rows[index][5].ToString();
            this.sportIDBox.Text = this.ds.Tables["Players"].Rows[index][1].ToString();
        }

        private static String GetConnectionString()
        {
            return "Data Source = ALENPC\\SQLEXPRESS;" +
                    "Initial Catalog = SportPerformance;" +
                    "Integrated Security = true;";
        }

        private void insertButton_click(Object sender, EventArgs e)
        {
            try
            {
                this.da.InsertCommand = new SqlCommand("insert into Players (player_id, sport_id, name, surname, date_of_birth, gender) values (@pid, @sid, @n, @s, @d, @g)", connectionString);

                this.da.InsertCommand.Parameters.Add("@pid", SqlDbType.Int).Value = Int32.Parse(pidBox.Text);
                this.da.InsertCommand.Parameters.Add("@sid", SqlDbType.Int).Value = Int32.Parse(sportIDBox.Text);
                this.da.InsertCommand.Parameters.Add("@n", SqlDbType.VarChar).Value = nameBox.Text;
                this.da.InsertCommand.Parameters.Add("@s", SqlDbType.VarChar).Value = surnameBox.Text;
                this.da.InsertCommand.Parameters.Add("@d", SqlDbType.VarChar).Value = dateBox.Text;
                this.da.InsertCommand.Parameters.Add("@g", SqlDbType.Char).Value = genderBox.Text;

                this.connectionString.Open();
                this.da.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Inserted succesfully");
                this.connectionString.Close();

                this.ds = new DataSet();
                this.da.Fill(this.ds, "Players");
                this.dgvPlayers.DataSource = this.ds.Tables["Players"];

                this.clearTextBoxes();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.connectionString.Close();
            }
        }

        private void deleteButton_click(object sender, EventArgs e)
        {
            int index = this.dgvPlayers.SelectedRows[0].Index;
            DialogResult dr;
            dr = MessageBox.Show("Are you sure?\n No undo after delete!", "Confirm Deletion", MessageBoxButtons.YesNo);
            if (dr == DialogResult.Yes)
            {

                // We create the delete command
                this.da.DeleteCommand = new SqlCommand("DELETE FROM Players WHERE player_id=@pid", connectionString);
                this.da.DeleteCommand.Parameters.Add("@pid", SqlDbType.Int).Value = this.ds.Tables["Players"].Rows[index][0];

                this.connectionString.Open();
                this.da.DeleteCommand.ExecuteNonQuery();
                MessageBox.Show("Deleted Succesfull from Database");
                this.connectionString.Close();

                this.sportIDBox.Clear();

                this.ds = new DataSet();
                this.da.Fill(this.ds, "Players");
                this.dgvPlayers.DataSource = this.ds.Tables["Players"];

                this.clearTextBoxes();
            }
            else
            {
                MessageBox.Show("Deletion Aborted");
                this.connectionString.Close();
            }
        }

        private void updateButton_click(object sender, EventArgs e)
        {
            try
            {
                // We take the index of the selected row
                int index = this.dgvPlayers.SelectedRows[0].Index;

                // We create the Update command
                this.da.UpdateCommand = new SqlCommand("Update Players set name = @n, surname = @s, date_of_birth = @d, gender = @g where player_id = @pid", this.connectionString);

                // We add the values for each parameter from the command
                this.da.UpdateCommand.Parameters.Add("@pid", SqlDbType.Int).Value = Int32.Parse(pidBox.Text);
                this.da.UpdateCommand.Parameters.Add("@sid", SqlDbType.Int).Value = Int32.Parse(sportIDBox.Text);
                this.da.UpdateCommand.Parameters.Add("@n", SqlDbType.VarChar).Value = nameBox.Text;
                this.da.UpdateCommand.Parameters.Add("@s", SqlDbType.VarChar).Value = surnameBox.Text;
                this.da.UpdateCommand.Parameters.Add("@d", SqlDbType.VarChar).Value = dateBox.Text;
                this.da.UpdateCommand.Parameters.Add("@g", SqlDbType.VarChar).Value = genderBox.Text;

                // We open the connection
                this.connectionString.Open();
                this.da.UpdateCommand.ExecuteNonQuery();
                MessageBox.Show("Updated Succesfull");
                this.connectionString.Close();

                // We repopulate the table
                this.ds = new DataSet();
                this.da.Fill(this.ds, "Players");
                this.dgvPlayers.DataSource = this.ds.Tables["Players"];

                this.clearTextBoxes();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.connectionString.Close();
            }
        }
    }
}