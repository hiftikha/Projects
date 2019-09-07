namespace LengthConverter
{
     partial class Length
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
               System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Length));
               this.ConvertButton = new System.Windows.Forms.Button();
               this.KilometerInputLabel = new System.Windows.Forms.Label();
               this.valueToConvert = new System.Windows.Forms.TextBox();
               this.convertTo = new System.Windows.Forms.ComboBox();
               this.convertedLabel = new System.Windows.Forms.Label();
               this.SuspendLayout();
               // 
               // ConvertButton
               // 
               this.ConvertButton.Font = new System.Drawing.Font("BatmanForeverAlternate", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
               this.ConvertButton.Location = new System.Drawing.Point(92, 245);
               this.ConvertButton.Name = "ConvertButton";
               this.ConvertButton.Size = new System.Drawing.Size(127, 40);
               this.ConvertButton.TabIndex = 0;
               this.ConvertButton.Text = "Convert";
               this.ConvertButton.UseVisualStyleBackColor = true;
               this.ConvertButton.Click += new System.EventHandler(this.ConvertButton_Click);
               // 
               // KilometerInputLabel
               // 
               this.KilometerInputLabel.AutoSize = true;
               this.KilometerInputLabel.Font = new System.Drawing.Font("BatmanForeverAlternate", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
               this.KilometerInputLabel.Location = new System.Drawing.Point(73, 85);
               this.KilometerInputLabel.Name = "KilometerInputLabel";
               this.KilometerInputLabel.Size = new System.Drawing.Size(173, 22);
               this.KilometerInputLabel.TabIndex = 1;
               this.KilometerInputLabel.Text = "Kilometer";
               // 
               // valueToConvert
               // 
               this.valueToConvert.Font = new System.Drawing.Font("BatmanForeverAlternate", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
               this.valueToConvert.Location = new System.Drawing.Point(92, 107);
               this.valueToConvert.Name = "valueToConvert";
               this.valueToConvert.Size = new System.Drawing.Size(127, 31);
               this.valueToConvert.TabIndex = 2;
               this.valueToConvert.Text = "0";
               this.valueToConvert.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
               this.valueToConvert.TextChanged += new System.EventHandler(this.valueToConvert_TextChanged);
               // 
               // convertTo
               // 
               this.convertTo.Font = new System.Drawing.Font("BatmanForeverAlternate", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
               this.convertTo.FormattingEnabled = true;
               this.convertTo.Location = new System.Drawing.Point(275, 167);
               this.convertTo.Name = "convertTo";
               this.convertTo.Size = new System.Drawing.Size(121, 30);
               this.convertTo.TabIndex = 3;
               this.convertTo.SelectionChangeCommitted += new System.EventHandler(this.convertTo_SelectionChangeCommitted);
               // 
               // convertedLabel
               // 
               this.convertedLabel.AutoSize = true;
               this.convertedLabel.Font = new System.Drawing.Font("BatmanForeverAlternate", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
               this.convertedLabel.Location = new System.Drawing.Point(275, 200);
               this.convertedLabel.Name = "convertedLabel";
               this.convertedLabel.Size = new System.Drawing.Size(141, 30);
               this.convertedLabel.TabIndex = 4;
               this.convertedLabel.Text = "Result\r\n";
               this.convertedLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
               this.convertedLabel.UseCompatibleTextRendering = true;
               this.convertedLabel.TextChanged += new System.EventHandler(this.convertedLabel_TextChanged);
               // 
               // Length
               // 
               this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
               this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
               this.ClientSize = new System.Drawing.Size(454, 428);
               this.Controls.Add(this.convertedLabel);
               this.Controls.Add(this.convertTo);
               this.Controls.Add(this.valueToConvert);
               this.Controls.Add(this.KilometerInputLabel);
               this.Controls.Add(this.ConvertButton);
               this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
               this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
               this.MaximizeBox = false;
               this.Name = "Length";
               this.Text = "Length Converter";
               this.ResumeLayout(false);
               this.PerformLayout();

          }

          #endregion

          private System.Windows.Forms.Button ConvertButton;
          private System.Windows.Forms.Label KilometerInputLabel;
          private System.Windows.Forms.TextBox valueToConvert;
          private System.Windows.Forms.ComboBox convertTo;
          public System.Windows.Forms.Label convertedLabel;
     }
}

