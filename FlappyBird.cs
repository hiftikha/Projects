using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using FlappyBird.Properties;
using System.Threading;
using System.Media;


namespace FlappyBird
{
     public partial class Form1 : Form
     {
          public Form1()
          {
               InitializeComponent();
          }

          List<int> Pipe1 = new List<int>();
          List<int> Pipe2 = new List<int>();
          int PipeWidth = 55;
          int PipeDifferenceY = 220;
          int PipeDifferenceX = 70;
          bool start = true;
          bool running;
          int step = 5;
          int OriginalX;
          int OriginalY;
          bool ResetPipes = false;
          int Points;
          int Score;
          bool inPipe = false;
          int ScoreDifference;

          public void Die()
          {
               running = false;
               timer2.Enabled = false;
               timer3.Enabled = false;
               StartButton.Visible = true;
               StartButton.Enabled = true;
               //ReadShowScore();
               Points = 0;
               Bird.Location = new Point(OriginalX, OriginalY);
               ResetPipes = true;
               Pipe1.Clear();

          }

          private void ReadShowScore()  // function for highscore log
          {
               using (StreamReader reader = new StreamReader("Score.ini"))  // C# uses streamreader to read from rext files, found in system.io
               {
                    Score = int.Parse(reader.ReadToEnd());
                    reader.Close();
                    if(int.Parse(ScoreLabel.Text) >= 0)
                    {
                         ScoreDifference = Score - int.Parse(ScoreLabel.Text) + 1;
                    }

                    if(Score < int.Parse(ScoreLabel.Text))
                    {
                         MessageBox.Show(string.Format("Test Score Lower"));
                         using (StreamWriter writer = new StreamWriter("Score.ini"))
                         {
                              writer.Write(ScoreLabel.Text);
                              writer.Close();
                         }
                    }
                    if (Score > int.Parse(ScoreLabel.Text))
                    {
                         MessageBox.Show(string.Format("Test Score Greater"));
                    }
                    if (Score == int.Parse(ScoreLabel.Text))
                    {
                         MessageBox.Show(string.Format("Test Score Equal"));
                    }
               }
          }

          private void StartGame()
          {
               ResetPipes = false;
               timer1.Enabled = true;  // timer running
               timer2.Enabled = true;  // timer running
               timer3.Enabled = true;  // timer running
               Random random = new Random();  set a new random variable
               int num = random.Next(40, this.Height - this.PipeDifferenceY);  // random.next(min,max)
               int num1 = num + this.PipeDifferenceY;
               Pipe1.Clear();
               Pipe1.Add(this.Width);
               Pipe1.Add(num);
               Pipe1.Add(this.Width);
               Pipe1.Add(num1);

               num = random.Next(40, this.Height - this.PipeDifferenceY);
               num1 = num + this.PipeDifferenceY;
               Pipe2.Clear();     
               Pipe2.Add(this.Width + PipeDifferenceX);
               Pipe2.Add(num);
               Pipe2.Add(this.Width + PipeDifferenceX);
               Pipe2.Add(num1);

               StartButton.Visible = false;
               StartButton.Enabled = false; // disable
               running = true;
               Focus();

          }
          private void StartButton_Click(object sender, EventArgs e)
          {
               StartGame();  // starts game when button pressed
          }

          private void timer1_Tick(object sender, EventArgs e)
          {
               this.Invalidate(); // refresh, update, invalidate methods
          }

          private void Form1_Load(object sender, EventArgs e)
          {
               OriginalX = Bird.Location.X;  // when form loads set the originalx and originaly to where bird is
               OriginalY = Bird.Location.Y;
               if(!File.Exists("Score.ini"))
               {
                    File.Create("Score.ini").Dispose();
               }
          }

          private void timer2_Tick(object sender, EventArgs e)
          {
               if(Pipe1[0] + PipeWidth <= 0 | start == true)
               {
                    Random rnd = new Random();
                    int px = this.Width;
                    int py = rnd.Next(40, (this.Height - PipeDifferenceY));
                    var p2x = px;
                    var p2y = py + PipeDifferenceY;
                    Pipe1.Clear();
                    Pipe1.Add(px);
                    Pipe1.Add(py);
                    Pipe1.Add(p2x);
                    Pipe1.Add(p2y);

               }
               else
               {
                    Pipe1[0] = Pipe1[0] - 2;
                    Pipe1[2] = Pipe1[2] - 2;
               }
               if (Pipe2[0] + PipeWidth <= 0)
               {
                    Random rnd = new Random();
                    int px = this.Width;
                    int py = rnd.Next(40, (this.Height - PipeDifferenceY));
                    var p2x = px;
                    var p2y = py + PipeDifferenceY;
                    int[] p1 = { px, py, p2x, p2y };
                    Pipe2.Clear();
                    Pipe2.Add(px);
                    Pipe2.Add(py);
                    Pipe2.Add(p2x);
                    Pipe2.Add(p2y);

               }
               else
               {
                    Pipe2[0] = Pipe2[0] - 2;
                    Pipe2[2] = Pipe2[2] - 2;
               }
          }

          private void Form1_Paint(object sender, PaintEventArgs e)  // creates pipes
          {
               if(!ResetPipes && Pipe1.Any() && Pipe2.Any())
               {
                    //Top of the top
                    e.Graphics.FillRectangle(Brushes.DarkViolet, new Rectangle(Pipe1[0], 0, PipeWidth, Pipe1[1]));
                    e.Graphics.FillRectangle(Brushes.DarkViolet, new Rectangle(Pipe1[0] - 10, Pipe1[3] - PipeDifferenceY, 75, 15));  // length,height

                    //First bottom
                    e.Graphics.FillRectangle(Brushes.DarkViolet, new Rectangle(Pipe1[2], Pipe1[3], PipeWidth, this.Height - Pipe1[3]));
                    e.Graphics.FillRectangle(Brushes.DarkViolet, new Rectangle(Pipe1[2] - 10, Pipe1[3], 75, 15)); // length,height
                    //The second from above
                    e.Graphics.FillRectangle(Brushes.DarkViolet, new Rectangle(Pipe2[0], 0, PipeWidth, Pipe2[1]));
                    e.Graphics.FillRectangle(Brushes.DarkViolet, new Rectangle(Pipe2[0] - 10, Pipe2[3] - PipeDifferenceY, 75, 15)); // length,height
                    //Second bottom
                    e.Graphics.FillRectangle(Brushes.DarkViolet, new Rectangle(Pipe2[2], Pipe2[3], PipeWidth, this.Height - Pipe2[3]));
                    e.Graphics.FillRectangle(Brushes.DarkViolet, new Rectangle(Pipe2[2] - 10, Pipe2[3], 75, 15));  // length,height
               }
          }

          private void CheckForPoint()
          {
               Rectangle rec = Bird.Bounds;
               Rectangle rec1 = new Rectangle(Pipe1[2] + 20, Pipe1[3] - PipeDifferenceY, 15, PipeDifferenceY);
               Rectangle rec2 = new Rectangle(Pipe2[2] + 20, Pipe2[3] - PipeDifferenceY, 15, PipeDifferenceY);
               Rectangle intersect1 = Rectangle.Intersect(rec, rec1);
               Rectangle intersect2 = Rectangle.Intersect(rec, rec2);
               if(!ResetPipes | start)
               {
                    if(intersect1 !=Rectangle.Empty | intersect2 !=Rectangle.Empty)
                    {
                         if(!inPipe)
                         {
                              Points++;
                              SoundPlayer sp = new SoundPlayer(FlappyBird.Properties.Resources.sfx_point);
                              sp.Play();
                              inPipe = true;
                         }
                    }
                    else
                    {
                         inPipe = false;
                    }
               }
          }

          private void CheckForCollision()
          {
               Rectangle rec = Bird.Bounds;
               Rectangle rec1 = new Rectangle(Pipe1[0], 0, PipeWidth, Pipe1[1]);
               Rectangle rec2 = new Rectangle(Pipe1[2], Pipe1[3], PipeWidth, this.Height - Pipe1[3]);
               Rectangle rec3 = new Rectangle(Pipe2[0], 0, PipeWidth, Pipe2[1]);
               Rectangle rec4 = new Rectangle(Pipe2[2], Pipe2[3], PipeWidth, this.Height - Pipe2[3]);
               Rectangle intersect1 = Rectangle.Intersect(rec, rec1);
               Rectangle intersect2 = Rectangle.Intersect(rec, rec2);
               Rectangle intersect3 = Rectangle.Intersect(rec, rec3);
               Rectangle intersect4 = Rectangle.Intersect(rec, rec4);

               if(!ResetPipes | start)
               {
                    if(intersect1 != Rectangle.Empty | intersect2 != Rectangle.Empty | intersect3 != Rectangle.Empty | intersect4 != Rectangle.Empty)
                    {
                         SoundPlayer sp = new SoundPlayer(FlappyBird.Properties.Resources.sfx_hit);
                         sp.Play();
                         Die();
                    }
               }
          }

          private void Form1_KeyDown(object sender, KeyEventArgs e)
          {
               switch(e.KeyCode)  // implemented a switch case statement, case for only SpaceKey
               {
                    case Keys.Space:
                         step = -4;
                         break;
               }
          }

          private void timer3_Tick(object sender, EventArgs e)
          {
               Bird.Location = new Point(Bird.Location.X, Bird.Location.Y + step);  // Logic
               if(Bird.Location.Y < 0)
               {
                    Bird.Location = new Point(Bird.Location.X, 0);
               }
               if(Bird.Location.Y + Bird.Height > this.ClientSize.Height)
               {
                    Bird.Location = new Point(Bird.Location.X, 0);
                    //Bird.Location = new Point(Bird.Location.X, this.ClientSize.Height - Bird.Height);
               }
               //CheckForCollision();
               if(running)
               {
                    CheckForPoint();  // Runs the function
               }
               ScoreLabel.Text = Convert.ToString(Points);  // ticker updates the score label
          }

          private void Form1_KeyUp(object sender, KeyEventArgs e)
          {
               switch(e.KeyCode)  // implemented a switch case statement, case for only SpaceKey
               {
                    case Keys.Space:
                         step = 4;
                         break;
               }
          }
     }
}
