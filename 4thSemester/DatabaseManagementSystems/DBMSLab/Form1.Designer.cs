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


namespace DBMSLab
{
    partial class Form1
    {
        private System.Windows.Forms.Button insertButton;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.Button deleteButton;

        private System.Windows.Forms.DataGridView parentTable;
        private System.Windows.Forms.DataGridView childTable;
        
        private System.Windows.Forms.TextBox midBox;
        private System.Windows.Forms.TextBox nameBox;
        private System.Windows.Forms.TextBox companyBox;
        private System.Windows.Forms.TextBox priceBox;
        private System.Windows.Forms.TextBox popularityBox;
        private System.Windows.Forms.TextBox typeIDBox;
        
        private System.Windows.Forms.Label midLabel;
        private System.Windows.Forms.Label nameLabel;
        private System.Windows.Forms.Label companyLabel;
        private System.Windows.Forms.Label priceLabel;
        private System.Windows.Forms.Label popularityLabel;
        private System.Windows.Forms.Label typeIDLabel;


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
            this.insertButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            this.parentTable = new System.Windows.Forms.DataGridView();
            this.childTable = new System.Windows.Forms.DataGridView();
            this.midBox = new System.Windows.Forms.TextBox();
            this.nameBox = new System.Windows.Forms.TextBox();
            this.priceBox = new System.Windows.Forms.TextBox();
            this.popularityBox = new System.Windows.Forms.TextBox();
            this.companyBox = new System.Windows.Forms.TextBox();
            this.typeIDBox = new System.Windows.Forms.TextBox();
            this.midLabel = new System.Windows.Forms.Label();
            this.companyLabel = new System.Windows.Forms.Label();
            this.nameLabel = new System.Windows.Forms.Label();
            this.priceLabel = new System.Windows.Forms.Label();
            this.popularityLabel = new System.Windows.Forms.Label();
            this.typeIDLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.parentTable)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.childTable)).BeginInit();
            this.SuspendLayout();
            // 
            // insertButton
            // 
            this.insertButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.insertButton.Location = new System.Drawing.Point(1177, 357);
            this.insertButton.Margin = new System.Windows.Forms.Padding(4);
            this.insertButton.Name = "insertButton";
            this.insertButton.Size = new System.Drawing.Size(295, 50);
            this.insertButton.TabIndex = 0;
            this.insertButton.Text = "Insert";
            this.insertButton.UseVisualStyleBackColor = true;
            this.insertButton.Click += new System.EventHandler(this.insertButton_click);
            // 
            // updateButton
            // 
            this.updateButton.Location = new System.Drawing.Point(1000, 478);
            this.updateButton.Margin = new System.Windows.Forms.Padding(4);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(295, 50);
            this.updateButton.TabIndex = 11;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_click);
            // 
            // deleteButton
            // 
            this.deleteButton.Location = new System.Drawing.Point(1387, 478);
            this.deleteButton.Margin = new System.Windows.Forms.Padding(4);
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.Size = new System.Drawing.Size(297, 50);
            this.deleteButton.TabIndex = 12;
            this.deleteButton.Text = "Delete";
            this.deleteButton.UseVisualStyleBackColor = true;
            this.deleteButton.Click += new System.EventHandler(this.deleteButton_click);
            // 
            // parentTable
            // 
            this.parentTable.AllowUserToAddRows = false;
            this.parentTable.AllowUserToDeleteRows = false;
            this.parentTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentTable.Location = new System.Drawing.Point(13, 13);
            this.parentTable.Margin = new System.Windows.Forms.Padding(4);
            this.parentTable.Name = "parentTable";
            this.parentTable.ReadOnly = true;
            this.parentTable.RowHeadersWidth = 51;
            this.parentTable.Size = new System.Drawing.Size(480, 225);
            this.parentTable.TabIndex = 1;
            this.parentTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.parentTable_click);
            // 
            // childTable
            // 
            this.childTable.AllowUserToAddRows = false;
            this.childTable.AllowUserToDeleteRows = false;
            this.childTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childTable.Location = new System.Drawing.Point(13, 293);
            this.childTable.Margin = new System.Windows.Forms.Padding(4);
            this.childTable.Name = "childTable";
            this.childTable.ReadOnly = true;
            this.childTable.RowHeadersWidth = 51;
            this.childTable.Size = new System.Drawing.Size(919, 269);
            this.childTable.TabIndex = 2;
            this.childTable.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.childTable_click);
            // 
            // midBox
            // 
            this.midBox.Location = new System.Drawing.Point(1177, 32);
            this.midBox.Margin = new System.Windows.Forms.Padding(4);
            this.midBox.Name = "midBox";
            this.midBox.Size = new System.Drawing.Size(195, 22);
            this.midBox.TabIndex = 3;
            // 
            // nameBox
            // 
            this.nameBox.Location = new System.Drawing.Point(1177, 69);
            this.nameBox.Margin = new System.Windows.Forms.Padding(4);
            this.nameBox.Name = "nameBox";
            this.nameBox.Size = new System.Drawing.Size(204, 22);
            this.nameBox.TabIndex = 4;
            // 
            // priceBox
            // 
            this.priceBox.Location = new System.Drawing.Point(1177, 150);
            this.priceBox.Margin = new System.Windows.Forms.Padding(4);
            this.priceBox.Name = "priceBox";
            this.priceBox.Size = new System.Drawing.Size(189, 22);
            this.priceBox.TabIndex = 5;
            // 
            // popularityBox
            // 
            this.popularityBox.Location = new System.Drawing.Point(1151, 187);
            this.popularityBox.Margin = new System.Windows.Forms.Padding(4);
            this.popularityBox.Name = "popularityBox";
            this.popularityBox.Size = new System.Drawing.Size(280, 22);
            this.popularityBox.TabIndex = 6;
            // 
            // companyBox
            // 
            this.companyBox.Location = new System.Drawing.Point(1177, 107);
            this.companyBox.Margin = new System.Windows.Forms.Padding(4);
            this.companyBox.Name = "companyBox";
            this.companyBox.Size = new System.Drawing.Size(200, 22);
            this.companyBox.TabIndex = 7;
            // 
            // typeIDBox
            // 
            this.typeIDBox.Location = new System.Drawing.Point(1192, 239);
            this.typeIDBox.Margin = new System.Windows.Forms.Padding(4);
            this.typeIDBox.Name = "typeIDBox";
            this.typeIDBox.Size = new System.Drawing.Size(183, 22);
            this.typeIDBox.TabIndex = 8;
            // 
            // midLabel
            // 
            this.midLabel.AutoSize = true;
            this.midLabel.Location = new System.Drawing.Point(980, 32);
            this.midLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.midLabel.Name = "midLabel";
            this.midLabel.Size = new System.Drawing.Size(98, 16);
            this.midLabel.TabIndex = 9;
            this.midLabel.Text = "Membership ID";
            // 
            // companyLabel
            // 
            this.companyLabel.AutoSize = true;
            this.companyLabel.Location = new System.Drawing.Point(997, 107);
            this.companyLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.companyLabel.Name = "companyLabel";
            this.companyLabel.Size = new System.Drawing.Size(65, 16);
            this.companyLabel.TabIndex = 13;
            this.companyLabel.Text = "Company";
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Location = new System.Drawing.Point(1008, 69);
            this.nameLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(44, 16);
            this.nameLabel.TabIndex = 10;
            this.nameLabel.Text = "Name";
            // 
            // priceLabel
            // 
            this.priceLabel.AutoSize = true;
            this.priceLabel.Location = new System.Drawing.Point(1008, 153);
            this.priceLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.priceLabel.Name = "priceLabel";
            this.priceLabel.Size = new System.Drawing.Size(38, 16);
            this.priceLabel.TabIndex = 11;
            this.priceLabel.Text = "Price";
            // 
            // popularityLabel
            // 
            this.popularityLabel.AutoSize = true;
            this.popularityLabel.Location = new System.Drawing.Point(997, 187);
            this.popularityLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.popularityLabel.Name = "popularityLabel";
            this.popularityLabel.Size = new System.Drawing.Size(67, 16);
            this.popularityLabel.TabIndex = 12;
            this.popularityLabel.Text = "Popularity";
            // 
            // typeIDLabel
            // 
            this.typeIDLabel.AutoSize = true;
            this.typeIDLabel.Location = new System.Drawing.Point(980, 239);
            this.typeIDLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.typeIDLabel.Name = "typeIDLabel";
            this.typeIDLabel.Size = new System.Drawing.Size(133, 16);
            this.typeIDLabel.TabIndex = 14;
            this.typeIDLabel.Text = "Membership Type ID";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1756, 608);
            this.Controls.Add(this.midBox);
            this.Controls.Add(this.midLabel);
            this.Controls.Add(this.priceBox);
            this.Controls.Add(this.priceLabel);
            this.Controls.Add(this.popularityBox);
            this.Controls.Add(this.popularityLabel);
            this.Controls.Add(this.companyBox);
            this.Controls.Add(this.companyLabel);
            this.Controls.Add(this.nameBox);
            this.Controls.Add(this.typeIDBox);
            this.Controls.Add(this.typeIDLabel);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.nameLabel);
            this.Controls.Add(this.childTable);
            this.Controls.Add(this.parentTable);
            this.Controls.Add(this.insertButton);
            this.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.form1_load);
            ((System.ComponentModel.ISupportInitialize)(this.parentTable)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.childTable)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
    }
}

