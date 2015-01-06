//------------------------------------------------------------------------------
// emRadioButton.h
//
// Copyright (C) 2005-2010,2014 Oliver Hamann.
//
// Homepage: http://eaglemode.sourceforge.net/
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License version 3 as published by the
// Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License version 3 for
// more details.
//
// You should have received a copy of the GNU General Public License version 3
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#ifndef emRadioButton_h
#define emRadioButton_h

#ifndef emCheckButton_h
#include <emCore/emCheckButton.h>
#endif

#ifndef emGroup_h
#include <emCore/emGroup.h>
#endif


//==============================================================================
//=============================== emRadioButton ================================
//==============================================================================

class emRadioButton : public emCheckButton {

public:

	// Class for a radio button. This is similar to a check button, but in a
	// set of radio buttons, only one button can have checked state, and the
	// user can unchecked a button only by checking another. That is the
	// usual behavior. Actually an emRadioButton does not modify its check
	// state on any click, as long as it is not a member of an
	// emRadioButton::Mechanism or emRadioButton::Group (it's not a must
	// to use these helper classes).

	emRadioButton(
		ParentArg parent, const emString & name,
		const emString & caption=emString(),
		const emString & description=emString(),
		const emImage & icon=emImage()
	);
		// Like emCheckButton.

	virtual ~emRadioButton();
		// Destructor. Removes the button from any Mechanism.

	class Mechanism : public emUncopyable {

	public:

		// Class for the mechanism of a set of radio buttons.

		Mechanism();
		virtual ~Mechanism();

		void Add(emRadioButton * radioButton);
			// Add a radio button to this mechanism. If the button
			// is already a member of another mechanism, it is
			// removed from that mechanism automatically.

		void AddAll(emPanel * parent);
			// Add all radio buttons which are children of the given
			// panel.

		void Remove(emRadioButton * radioButton);
		void RemoveByIndex(int index);
			// Remove a radio button from this mechanism.

		void RemoveAll();
			// Remove all radio buttons from this mechanism.

		const emSignal & GetCheckSignal() const;
			// This signal is signaled whenever there was a change
			// in the result of GetChecked().

		emRadioButton * GetChecked();
		const emRadioButton * GetChecked() const;
		void SetChecked(emRadioButton * radioButton);
			// Get/set the member button which is currently checked.
			// NULL means to have no member button checked.

		int GetCheckIndex();
		void SetCheckIndex(int index);
			// Get/set the index of the member button which is
			// currently checked. -1 means to have no member button
			// checked.

		int GetCount();
			// Get number of member buttons.

		int GetIndexOf(const emRadioButton * button) const;
			// Get the index of a member button, or -1 if not found.

	protected:

		virtual void CheckChanged();
			// Called whenever there was a change in the result of
			// GetChecked().

	private:

		emArray<emRadioButton *> Array;
		emSignal CheckSignal;
		int CheckIndex;
	};

	class Group : public emGroup, public Mechanism {

	public:

		// Combination of emGroup and Mechanism. Any radio buttons
		// created as children of such a group are added automatically
		// to the mechanism (this magic happens in the constructor of
		// emRadioButton).

		Group(
			ParentArg parent, const emString & name,
			const emString & caption=emString(),
			const emString & description=emString(),
			const emImage & icon=emImage()
		);
			// Like the constructor of emGroup.

		virtual ~Group();
			// Destructor.
	};

protected:

	virtual void Clicked();

	virtual void CheckChanged();

	virtual emString GetHowTo();

private:

	friend class Mechanism;

	Mechanism * Mech;
	int MechIndex;

	static const char * HowToRadioButton;
};

inline const emSignal & emRadioButton::Mechanism::GetCheckSignal() const
{
	return CheckSignal;
}

inline emRadioButton * emRadioButton::Mechanism::GetChecked()
{
	return CheckIndex>=0 ? Array[CheckIndex] : NULL;
}

inline const emRadioButton * emRadioButton::Mechanism::GetChecked() const
{
	return CheckIndex>=0 ? Array[CheckIndex] : NULL;
}

inline int emRadioButton::Mechanism::GetCheckIndex()
{
	return CheckIndex;
}

inline int emRadioButton::Mechanism::GetCount()
{
	return Array.GetCount();
}

inline int emRadioButton::Mechanism::GetIndexOf(
	const emRadioButton * button
) const
{
	return button && button->Mech==this ? button->MechIndex : -1;
}


#endif