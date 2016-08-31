/***
  This file is part of pavucontrol.

  Copyright 2006-2008 Lennart Poettering
  Copyright 2009 Colin Guthrie

  pavucontrol is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  pavucontrol is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with pavucontrol. If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef devicewidget_h
#define devicewidget_h

#include "pavucontrol.h"

#include "minimalstreamwidget.h"
#include "ui_devicewidget.h"

class MainWindow;
class ChannelWidget;

class DeviceWidget : public MinimalStreamWidget, public Ui::DeviceWidget {
    Q_OBJECT
public:
    DeviceWidget(QWidget* parent=nullptr);
    void init(MainWindow* mainWindow, Glib::ustring);

    void setChannelMap(const pa_channel_map &m, bool can_decibel);
    void setVolume(const pa_cvolume &volume, bool force = false);
    virtual void updateChannelVolume(int channel, pa_volume_t v);

    void hideLockedChannels(bool hide = true);

    Glib::ustring name;
    Glib::ustring description;
    uint32_t index, card_index;

    /*
    Gtk::ToggleButton *lockToggleButton, *muteToggleButton, *defaultToggleButton;
    Gtk::SpinButton *offsetButton;
    */

    bool offsetButtonEnabled;

    pa_channel_map channelMap;
    pa_cvolume volume;

    ChannelWidget *channelWidgets[PA_CHANNELS_MAX];

    virtual void onMuteToggleButton();
    virtual void onLockToggleButton();
    virtual void onDefaultToggleButton();
    virtual void setDefault(bool isDefault);
    // virtual bool onContextTriggerEvent(GdkEventButton*);
    virtual void setLatencyOffset(int64_t offset);
    void onOffsetChange();

    sigc::connection timeoutConnection;

    bool timeoutEvent();

    virtual void executeVolumeUpdate();
    virtual void setBaseVolume(pa_volume_t v);

    std::vector< std::pair<Glib::ustring,Glib::ustring> > ports;
    Glib::ustring activePort;

    void prepareMenu();

    void renamePopup();

protected:
    MainWindow *mpMainWindow;

    virtual void onPortChange() = 0;

    // Gtk::Menu contextMenu;
    // Gtk::MenuItem rename;

#if 0
    /* Tree model columns */
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
      public:

        ModelColumns()
        { add(name); add(desc); }

        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<Glib::ustring> desc;
    };

    ModelColumns portModel;
    Gtk::Expander *advancedOptions;
    Gtk::HBox *portSelect, *offsetSelect;
    Gtk::ComboBox *portList;
    Glib::RefPtr<Gtk::ListStore> treeModel;
    Glib::RefPtr<Gtk::Adjustment> offsetAdjustment;
#endif

private:
    Glib::ustring mDeviceType;

};

#endif
