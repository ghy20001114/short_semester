Blockly.Blocks['sorte'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("传送带");
    this.appendDummyInput()
        .appendField(new Blockly.FieldNumber(0), "conveyor_num");
    this.appendDummyInput()
        .appendField("分拣器旋转到")
        .appendField(new Blockly.FieldAngle(0), "sorte_ang");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour("#88A705");
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['var_convert'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("传送带")
        .appendField(new Blockly.FieldNumber(0), "convert_num");
    this.setOutput(true, null);
    this.setColour("#88A705");
 this.setTooltip("");
 this.setHelpUrl("");
  }
};


Blockly.Blocks['node_red_return'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("将");
    this.appendValueInput("NAME")
        .setCheck("String");
    this.appendDummyInput()
        .appendField("发送到下一个节点");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setColour("#88A705");
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['conveyor_speed'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("传送带");
    this.appendDummyInput()
        .appendField(new Blockly.FieldNumber(0), "conveyor_num");
    this.appendDummyInput()
        .appendField("以")
        .appendField(new Blockly.FieldNumber(0), "NAME");
    this.appendDummyInput()
        .appendField("速度向")
        .appendField(new Blockly.FieldDropdown([["正方向","1"], ["反方向","0"]]), "dir");
    this.appendDummyInput()
        .appendField("运行");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour("#88A705");
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['photogate'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("传送带");
    this.appendDummyInput()
        .appendField(new Blockly.FieldNumber(0), "conveyor_num");
    this.appendDummyInput()
        .appendField("的")
        .appendField(new Blockly.FieldDropdown([["前置","1"], ["后置","2"]]), "photogate_val")
        .appendField("光电门状态");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(210);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};
//car*********************************************************************************************************************car
Blockly.Blocks['car'] = {
    init: function() {
      this.appendDummyInput()
          .appendField("车")
          .appendField(new Blockly.FieldTextInput("1"), "carid")
          .appendField("以")
          .appendField(new Blockly.FieldNumber(100, -1), "speed")
          .appendField("的速度向")
          .appendField(new Blockly.FieldDropdown([["左","0"], ["右","1"]]), "dir")
          .appendField("偏")
          .appendField(new Blockly.FieldAngle(0), "dgr")
          .appendField("前进（")
          .appendField("P:")
          .appendField(new Blockly.FieldNumber(10, 0), "P")
          .appendField("I:")
          .appendField(new Blockly.FieldNumber(10, 0), "I")
          .appendField("D:")
          .appendField(new Blockly.FieldNumber(10, 0), "D")
          .appendField("）");
      this.setInputsInline(true);
      this.setPreviousStatement(true, null);
      this.setNextStatement(true, null);
      this.setColour("#8B6508");
   this.setTooltip("");
   this.setHelpUrl("");
    }
  };

  Blockly.Blocks['car_id'] = {
    init: function() {
      this.appendDummyInput()
          .appendField("车")
          .appendField(new Blockly.FieldTextInput("1"), "id");
      this.setOutput(true, null);
      this.setColour("#8B6508");
   this.setTooltip("");
   this.setHelpUrl("");
    }
  };

  Blockly.Blocks['mobilenet'] = {
    init: function() {
      this.appendDummyInput()
          .appendField("识别结果是")
          .appendField(new Blockly.FieldTextInput("物体名称"), "NAME");
      this.setInputsInline(true);
      this.setOutput(true, null);
      this.setColour("#F6921E");
   this.setTooltip("");
   this.setHelpUrl("");
    }
  };


  Blockly.Blocks['rgb_id'] = {
    init: function() {
      this.appendDummyInput()
          .appendField("RGB灯")
          .appendField(new Blockly.FieldNumber(0, 0), "id");
      this.setOutput(true, null);
      this.setColour(180);
   this.setTooltip("");
   this.setHelpUrl("");
    }
  };
  Blockly.Blocks['rgb'] = {
    init: function() {
      this.appendValueInput("NAME")
          .setCheck("Colour")
          .appendField("将RGB灯")
          .appendField(new Blockly.FieldNumber(0, 0), "id")
          .appendField("颜色设置为");
      this.setInputsInline(false);
      this.setPreviousStatement(true, null);
      this.setNextStatement(true, null);
      this.setColour(180);
   this.setTooltip("");
   this.setHelpUrl("");
    }
  };


  
  Blockly.Blocks['led_b_to_d'] = {
    init: function() {
      this.appendValueInput("which_LED")
          .setCheck("String")
          .appendField("which_LED");
      this.appendValueInput("1")
          .setCheck("String")
          .appendField("1");
      this.appendValueInput("2")
          .setCheck("String")
          .appendField("2");
      this.appendValueInput("3")
          .setCheck("String")
          .appendField("3");
      this.appendValueInput("4")
          .setCheck("String")
          .appendField("4");
      this.appendValueInput("5")
          .setCheck("String")
          .appendField("5");
      this.appendValueInput("6")
          .setCheck("String")
          .appendField("6");
      this.appendValueInput("7")
          .setCheck("String")
          .appendField("7");
      this.appendValueInput("8")
          .setCheck("String")
          .appendField("8");
      this.setPreviousStatement(true, null);
      this.setColour(250);
   this.setTooltip("");
   this.setHelpUrl("");
    }
  };


