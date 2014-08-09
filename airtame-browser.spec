Summary:	AIRTAME Browser
Name:		airtame-browser
Version:	%(echo -n `date +"%Y%m%d_"`; git describe --abbrev=6 --always --dirty |sed "s/-/_/g")
Release:	1%{?dist}
License:	GPL v2
URL:		http://www.airtame.com
BuildRequires:	gcc-c++ make
Requires:	qt-airtame-libs

%define _builddir %(echo $PWD)

%description
AIRTAME Browser

%prep

%build
qmake -config release

%install
install -d %{buildroot}/opt/airtame-browser/
cp airtame-browser %{buildroot}/opt/airtame-browser/
install -Dm644 airtamebrowser.service %{buildroot}%{_libdir}/systemd/system/airtamebrowser.service

%clean

%files
/opt/airtame-browser/airtame-browser
%{_libdir}/systemd/system/airtamebrowser.service
