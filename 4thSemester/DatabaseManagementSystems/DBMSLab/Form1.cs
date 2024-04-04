using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace DBMSLab
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
            this.typeIDBox.ReadOnly = true;
            this.childTable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
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
            this.parentTable.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            this.da.SelectCommand = new SqlCommand("select * from MembershipTypes", connectionString);
            this.ds.Clear();
            this.da.Fill(this.ds, "MembershipTypes");

            this.parentTable.DataSource = this.ds.Tables["MembershipTypes"];
        }

        private void form1_load(object sender, EventArgs e)
        {

        }

        private void clearTextBoxes()
        {
            this.midBox.Clear();
            this.nameBox.Clear();
            this.popularityBox.Clear();
            this.priceBox.Clear();
            this.companyBox.Clear();   
            this.typeIDBox.Clear();
        }

        private void parentTable_click(object sender, DataGridViewCellEventArgs e)
        {
            this.clearTextBoxes();
            DataGridViewRow selectedParent = this.parentTable.SelectedRows[0];
            this.typeIDBox.Text = selectedParent.Cells[0].Value.ToString();

            if(this.parentTable.SelectedRows.Count > 0)
            {
                int membershipTypeID = Convert.ToInt32(selectedParent.Cells[0].Value);

                this.da.SelectCommand = new SqlCommand("select * from Memberships where membershiptype_id = @id", this.connectionString);
                this.da.SelectCommand.Parameters.AddWithValue("@id", membershipTypeID);

                this.ds = new DataSet();
                this.da.Fill(this.ds, "Memberships");
                this.childTable.DataSource = this.ds.Tables["Memberships"];
            }
        }

        private void childTable_click(Object sender, DataGridViewCellEventArgs e)
        {
            int index = this.childTable.SelectedRows[0].Index;

            this.midBox.Text = this.ds.Tables["Memberships"].Rows[index][0].ToString();
            this.nameBox.Text = this.ds.Tables["Memberships"].Rows[index][1].ToString();
            this.companyBox.Text = this.ds.Tables["Memberships"].Rows[index][2].ToString();
            this.priceBox.Text = this.ds.Tables["Memberships"].Rows[index][3].ToString();
            this.popularityBox.Text = this.ds.Tables["Memberships"].Rows[index][4].ToString();
            this.typeIDBox.Text = this.ds.Tables["Memberships"].Rows[index][5].ToString();
        }

        private static String GetConnectionString()
        {
            return "Data Source = ALENPC\\SQLEXPRESS;" +
                    "Initial Catalog = GSM;" +
                    "Integrated Security = true;";
        }

        private void insertButton_click(Object sender, EventArgs e)
        {
            try
            {
                this.da.InsertCommand = new SqlCommand("insert into Memberships (mid, membership_name, membership_company, membership_price, membership_popularity, membershiptype_id) values (@mid, @n, @c, @pr, @pop, @mtid)", connectionString);

                this.da.InsertCommand.Parameters.Add("@mid", SqlDbType.Int).Value = Int32.Parse(midBox.Text);
                this.da.InsertCommand.Parameters.Add("@n", SqlDbType.VarChar).Value = nameBox.Text;
                this.da.InsertCommand.Parameters.Add("@c", SqlDbType.VarChar).Value = companyBox.Text;
                this.da.InsertCommand.Parameters.Add("@pr", SqlDbType.Int).Value = Int32.Parse(priceBox.Text);
                this.da.InsertCommand.Parameters.Add("@pop", SqlDbType.Int).Value = Int32.Parse(popularityBox.Text);
                this.da.InsertCommand.Parameters.Add("@mtid", SqlDbType.Int).Value = Int32.Parse(typeIDBox.Text);

                this.connectionString.Open();
                this.da.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Inserted succesfully");
                this.connectionString.Close();

                this.ds = new DataSet();
                this.da.Fill(this.ds, "Memberships");
                this.childTable.DataSource = this.ds.Tables["Memberships"];

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
            int index = this.childTable.SelectedRows[0].Index;
            DialogResult dr;
            dr = MessageBox.Show("Are you sure?\n No undo after delete!", "Confirm Deletion", MessageBoxButtons.YesNo);
            if (dr == DialogResult.Yes)
            {

                // We create the delete command
                this.da.DeleteCommand = new SqlCommand("DELETE FROM Memberships WHERE mid=@id", connectionString);
                this.da.DeleteCommand.Parameters.Add("@id", SqlDbType.Int).Value = this.ds.Tables["Memberships"].Rows[index][0];

                this.connectionString.Open();
                this.da.DeleteCommand.ExecuteNonQuery();
                MessageBox.Show("Deleted Succesfull from Database");
                this.connectionString.Close();

                this.typeIDBox.Clear();

                this.ds = new DataSet();
                this.da.Fill(this.ds, "Memberships");
                this.childTable.DataSource = this.ds.Tables["Memberships"];

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
                int index = this.childTable.SelectedRows[0].Index;

                // We create the Update command
                this.da.UpdateCommand = new SqlCommand("Update Memberships set membership_name = @n, membership_company = @c, membership_price = @pr, membership_popularity = @pop where mid = @mid", this.connectionString);

                // We add the values for each parameter from the command
                this.da.UpdateCommand.Parameters.Add("@n", SqlDbType.VarChar).Value = nameBox.Text;
                this.da.UpdateCommand.Parameters.Add("@c", SqlDbType.VarChar).Value = companyBox.Text;
                this.da.UpdateCommand.Parameters.Add("@pr", SqlDbType.Int).Value = Int32.Parse(priceBox.Text);
                this.da.UpdateCommand.Parameters.Add("@pop", SqlDbType.Int).Value = Int32.Parse(popularityBox.Text);
                this.da.UpdateCommand.Parameters.Add("@mid", SqlDbType.Int).Value = this.ds.Tables["Memberships"].Rows[index][0];

                // We open the connection
                this.connectionString.Open();
                this.da.UpdateCommand.ExecuteNonQuery();
                MessageBox.Show("Updated Succesfull");
                this.connectionString.Close();

                // We repopulate the table
                this.ds = new DataSet();
                this.da.Fill(this.ds, "Memberships");
                this.childTable.DataSource = this.ds.Tables["Memberships"];

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
