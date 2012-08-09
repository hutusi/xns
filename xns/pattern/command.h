
#pragma once

class Command{
	friend class CommandExecuter;
public:
	Command() : undo_(0) {} 
	virtual ~Command() {}

private:
	virtual void execute() = 0;
	inline Command* undo() { 
		if (!undo_) { undo_->execute(); } 
	}
	inline void redo() { execute(); }

private:
	Command* undo_;
};
