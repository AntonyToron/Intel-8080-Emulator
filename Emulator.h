/*
  File name : Emulator.h
  Author : Antony Toron

  Description : This defines the interface for the emulator and declares
  the wxwidgets app.

 */

class Emulator : public wxApp {
 public:
  virtual bool OnInit(); // DECLARED AS VIRTUAL SO THAT WXAPP DEFAULT IS OVERWRITTEN
};

class MainFrame : public wxFrame {
 public:
  MainFrame(const wxChar *title, int x, int y, int width, int height);
  ~MainFrame();
};
  