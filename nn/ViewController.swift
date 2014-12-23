//
//  ViewController.swift
//  nn
//
//  Created by Bent Cardan on 12/23/14.
//  Copyright (c) 2014 Bent Cardan. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITextFieldDelegate {

  @IBOutlet weak var simpleTextField: UITextField!
  
  @IBOutlet weak var simpleLabel: UILabel!
  
  @IBAction func changeLabel(sender: AnyObject) {
    simpleLabel.text = "Hello, " + simpleTextField.text + "!"
    self.simpleTextField.resignFirstResponder()
  }
  
  func textFieldShouldReturn(textField: UITextField) -> Bool {
    simpleLabel.text = "Hello, " + simpleTextField.text + "!"
    textField.resignFirstResponder()
    return false
  }
  
  override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
    self.view.endEditing(true)
  }
  
  override func viewDidLoad() {
    super.viewDidLoad()
    
    //@IBAction this is something the user touches
    //@IBOutlet some function or thing sets the view object
    //@IBAction && @IBOutlet
    
    
  }

  override func didReceiveMemoryWarning() {
    super.didReceiveMemoryWarning()
    // Dispose of any resources that can be recreated.
  }


}

