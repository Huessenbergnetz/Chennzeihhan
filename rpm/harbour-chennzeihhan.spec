# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.27
# 

Name:       harbour-chennzeihhan

# >> macros
%define __provides_exclude_from ^%{_datadir}/%{name}/de/huessenbergnetz/.*$
# << macros

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}
Summary:    Offline Car License Plate Database for SailfishOS
Version:    1.3.0
Release:    2
Group:      Qt/Qt
License:    GPL-2.0
URL:        https://www.buschmann23.de/entwicklung/anwendungen/chennzeihhan/
Source0:    %{name}-%{version}.tar.bz2
Source100:  harbour-chennzeihhan.yaml
Requires:   qt5-qtdeclarative-import-xmllistmodel
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(sailfishapp) >= 0.0.10
BuildRequires:  pkgconfig(sailfishsilica)
BuildRequires:  pkgconfig(sqlite3)
BuildRequires:  desktop-file-utils

%description
Chennzeihhan (old high german for Kennzeichen/registration plate) is an offline database for vehicle registration plates that can find the district of the vehicle plate. It covers currently more than 800 district codes from Germany and Switzerland.


%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qtc_qmake5 

%qtc_make %{?_smp_mflags}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%qmake5_install

# >> install post
# << install post

desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%defattr(644, root, root, 755)
%attr(755, root, root) %{_bindir}/harbour-chennzeihhan
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
# >> files
# << files
