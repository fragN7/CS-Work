namespace DBMSLab2
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.parentTable = new System.Windows.Forms.DataGridView();
            this.childTable = new System.Windows.Forms.DataGridView();
            this.insertButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            this.panel = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.parentTable)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.childTable)).BeginInit();
            this.SuspendLayout();
            // 
            // parentTable
            // 
            this.parentTable.AllowUserToAddRows = false;
            this.parentTable.AllowUserToDeleteRows = false;
            this.parentTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentTable.Location = new System.Drawing.Point(12, 22);
            this.parentTable.Name = "parentTable";
            this.parentTable.ReadOnly = true;
            this.parentTable.Size = new System.Drawing.Size(587, 350);
            this.parentTable.TabIndex = 0;
            this.parentTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.parentTable_CellClick);
            // 
            // childTable
            // 
            this.childTable.AllowUserToAddRows = false;
            this.childTable.AllowUserToDeleteRows = false;
            this.childTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childTable.Location = new System.Drawing.Point(632, 22);
            this.childTable.Name = "childTable";
            this.childTable.ReadOnly = true;
            this.childTable.Size = new System.Drawing.Size(587, 350);
            this.childTable.TabIndex = 1;
            this.childTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.childTable_CellClick);
            // 
            // insertButton
            // 
            this.insertButton.Location = new System.Drawing.Point(39, 409);
            this.insertButton.Name = "insertButton";
            this.insertButton.Size = new System.Drawing.Size(158, 34);
            this.insertButton.TabIndex = 2;
            this.insertButton.Text = "Insert";
            this.insertButton.UseVisualStyleBackColor = true;
            this.insertButton.Click += new System.EventHandler(this.insertButton_Click);
            // 
            // deleteButton
            // 
            this.deleteButton.Location = new System.Drawing.Point(39, 480);
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.Size = new System.Drawing.Size(158, 34);
            this.deleteButton.TabIndex = 3;
            this.deleteButton.Text = "Delete";
            this.deleteButton.UseVisualStyleBackColor = true;
            this.deleteButton.Click += new System.EventHandler(this.deleteButton_Click);
            // 
            // updateButton
            // 
            this.updateButton.Location = new System.Drawing.Point(39, 557);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(158, 34);
            this.updateButton.TabIndex = 4;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // panel
            // 
            this.panel.Location = new System.Drawing.Point(245, 399);
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(956, 203);
            this.panel.TabIndex = 5;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1231, 614);
            this.Controls.Add(this.panel);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.insertButton);
            this.Controls.Add(this.childTable);
            this.Controls.Add(this.parentTable);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.parentTable)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.childTable)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView parentTable;
        private System.Windows.Forms.DataGridView childTable;
        private System.Windows.Forms.Button insertButton;
        private System.Windows.Forms.Button deleteButton;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.Panel panel;
    }
}
