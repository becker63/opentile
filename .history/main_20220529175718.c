 Atom a = XInternAtom(m_pDisplay, "_NET_CLIENT_LIST" , true);
    Atom actualType;
    int format;
    unsigned long numItems, bytesAfter;
    unsigned char *data =0;
    int status = XGetWindowProperty(m_pDisplay,
                                rootWindow,
                                a,
                                0L,
                                (~0L),
                                false,
                                AnyPropertyType,
                                &actualType,
                                &format,
                                &numItems,
                                &bytesAfter,
                                &data);

    if (status >= Success && numItems)
    {
        // success - we have data: Format should always be 32:
        Q_ASSERT(format == 32);
        // cast to proper format, and iterate through values:
        quint32 *array = (quint32*) data;
        for (quint32 k = 0; k < numItems; k++)
        {
            // get window Id:
            Window w = (Window) array[k];

            qDebug() << "Scanned client window:" << w;
        }
        XFree(data);
    }
Share
Edit
